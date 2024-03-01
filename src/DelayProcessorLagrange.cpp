/*
  ==============================================================================

    DelayProcessor.cpp
    Created: 10 Oct 2023 10:54:31am
    Author:  Micha

  ==============================================================================
*/

#include "DelayProcessorLagrange.h"
//#include "DelayLineBase.h"


/* sampleRate gets passed ONCE upon calling constructor */

DelayProcessor::DelayProcessor() {
    maxDelayTime = 2;
    lowpassFreq = 20000.0;
    delayLine = juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd>();
    *filter.state = *dsp::FilterDesign<float>::designFIRLowpassWindowMethod(20000.0, 48000.0, 21, dsp::WindowingFunction<float>::hamming);
    position = juce::Vector3D<float>(0, 0, 0);
    azimuth = elevation = 0.f;
    currentDelayInSamples = currentDelayTime = 0;
    distance = gainFactor = 1;
    fs = 48000.f;
    isActive = true;
}

DelayProcessor::DelayProcessor(double maxDelayTimeInSeconds, double sampleRate) :
    maxDelayTime(maxDelayTimeInSeconds), fs(sampleRate)
    //delayLine(sampleRate * maxDelayTimeInSeconds) 
{   
    delayLine = juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd>();
    setMaxDelayTime(maxDelayTimeInSeconds, sampleRate);
    lowpassFreq = 20000.0;
    *filter.state = *dsp::FilterDesign<float>::designFIRLowpassWindowMethod(20000.0, sampleRate, 21, dsp::WindowingFunction<float>::hamming);
    position = juce::Vector3D<float>(0, 0, 0);
    azimuth = elevation = 0.f;
    currentDelayInSamples = currentDelayTime = 0;
    distance = gainFactor = 1;
    isActive = true;
}

DelayProcessor::DelayProcessor(DelayProcessor&& other) noexcept
    : maxDelayTime(other.maxDelayTime),
    azimuth(other.azimuth),
    currentDelayInSamples(other.currentDelayInSamples),
    currentDelayTime(other.currentDelayTime),
    distance(other.distance),
    elevation(other.elevation),
    fs(other.fs),
    gainFactor(other.gainFactor),
    isActive(other.isActive),
    lowpassFreq(other.lowpassFreq),
    delayLine(std::move(other.delayLine)),  // Move the delayLine
    filter(std::move(other.filter)),        // Move the filter
    mirExcerpt(std::move(other.mirExcerpt)),
    position(std::move(other.position))     // Move the position
{
    // Ensure to leave the moved-from object in a valid state
    // ...
}

DelayProcessor::~DelayProcessor() {
    //delete delayLineBase->delayLine;
}

void DelayProcessor::setPosition(float newX, float newY, float newZ)
{
    position.x = newX;
    position.y = newY;
    position.z = newZ;
}

void DelayProcessor::setPosition(const juce::Vector3D<float>& newPos)
{
    position = newPos;
}

/* 
    This will be called via GUI slider action --> should be only interface to the DelayProcessor
    Handling of Gain Factor and Delay Time will be handled in here and passed on to DelayProcessor internally
    Remember to fetch gainFactor in inputCoordsView.sliderValueChanged() and from there pass it on to src_gains[]
*/
void DelayProcessor::setDistance(float newDistance)
{
    distance = newDistance;

    // calculate new gain; actual gain handling happening in binauraliser.c, though
    //gainFactor = std::clamp(1.0f / distance, 0.0f, 1.0f);

    // Set Delay
    float delayInSamples = newDistance * (fs / SONIC_SPEED); // SONIC_SPEED defined in _common.h
    setDelayTimeInSamples(delayInSamples, fs); // watch out for potential mismatch of "fs" and host sample rate!!!
}

void DelayProcessor::setFirFilter(double freq, double sampleRate) {
    *filter.state = *dsp::FilterDesign<float>::designFIRLowpassWindowMethod(freq, sampleRate, 21, dsp::WindowingFunction<float>::hamming);
    lowpassFreq = freq;
}

/**
*   Receives the rir from PluginProcessor (which in return got it from te psx struct) and uses
*   start and end indices to cut and copy an excerpt to the internal buffer
*/
void DelayProcessor::setRirExcerpt(const juce::AudioBuffer<float>& rir, int mirStartIndex, int mirEndIndex,
                                   juce::dsp::ProcessSpec& spec)
{
    jassert(mirStartIndex > 0);
    jassert(mirEndIndex > 0);
    mirExcerpt.setSize(1, mirEndIndex - mirStartIndex + 1, false, true, true);

    // it will always be 1 channel, but maaaybe
    for (int channel = 0; channel < rir.getNumChannels(); ++channel) {
        int i = 0;
        for (int idx = mirStartIndex - 1; idx < mirEndIndex; ++idx, ++i) {
            mirExcerpt.setSample(channel, i, rir.getSample(channel, idx));
        }
    }
    convolver.loadImpulseResponse(std::move(mirExcerpt), spec.sampleRate, juce::dsp::Convolution::Stereo::no, juce::dsp::Convolution::Trim::no, juce::dsp::Convolution::Normalise::no);
    // sometimes reset and prepare are called here, but it shouldn't be necessary
    convolver.reset();
    convolver.prepare(spec);
}

/* Obsolete? */
void DelayProcessor::setDelayTime(double delayTimeInSeconds, double sampleRate) {
    double clampedDelayTime = juce::jlimit(0.0, maxDelayTime, delayTimeInSeconds);
    delayLine.setDelay(clampedDelayTime * sampleRate);
    //delayLineBase->setDelay(clampedDelayTime * sampleRate);
    currentDelayTime = clampedDelayTime;
}

void DelayProcessor::setDelayTimeInSamples(float delayTimeInSamples, double sampleRate) {
    delayLine.setDelay(delayTimeInSamples);
    currentDelayInSamples = delayTimeInSamples;
    currentDelayTime = delayTimeInSamples / sampleRate; // in seconds
}

void DelayProcessor::setMaxDelayTime(double maxDelayTimeInSeconds, double sampleRate) {
    //delayLineBase->setMaximumDelayInSamples(sampleRate * maxDelayTimeInSeconds);
    delayLine.setMaximumDelayInSamples(sampleRate * maxDelayTimeInSeconds);
    maxDelayTime = maxDelayTimeInSeconds;
}

void DelayProcessor::prepare(juce::dsp::ProcessSpec& spec) {
    delayLine.prepare(spec);
    setMaxDelayTime(maxDelayTime, spec.sampleRate);
    filter.reset();
    filter.prepare(spec);
    convolver.reset();
    convolver.prepare(spec);
}

// Not used
void DelayProcessor::processBlock(juce::dsp::AudioBlock<float>& block) { 
    delayLine.process(juce::dsp::ProcessContextReplacing<float>(block));
    //convolver.process(block);
}

void DelayProcessor::process(juce::dsp::ProcessContextReplacing<float>& context) {
    delayLine.process(context);
    //filter.process(context);
    convolver.process(context);
}
