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
    delayLine = juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd>();
    delayLineLP = std::make_unique<DelayLineLP>();
    delayLineLP->initFilter(48000);
    //delayLineTIPS = DelayLineTIPS();
    position = juce::Vector3D<float>(0, 0, 0);
    initCoords = {}; // curly braces to initialize all vars with 0.0
    currentAzimuth = currentElevation = 0.f;
    currentDelayInSamples = currentDelayTime = 0;
    currentDistance = initCoords.distance = 1.f;
    gainFactor = 1.f;
    fs = 48000.f; // create setter to call in prepareToPlay() !!!
    isActive = true;
}

DelayProcessor::DelayProcessor(double maxDelayTimeInSeconds, double sampleRate) :
    maxDelayTime(maxDelayTimeInSeconds), fs(sampleRate)
    //delayLine(sampleRate * maxDelayTimeInSeconds) 
{   
    delayLine = juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd>();
    delayLineLP = std::make_unique<DelayLineLP>();
    delayLineLP->initFilter(fs);
    //delayLineTIPS = DelayLineTIPS();
    setMaxDelayTime(maxDelayTimeInSeconds, sampleRate);
    position = juce::Vector3D<float>(0, 0, 0);
    initCoords = {}; // curly braces to initialize all vars with 0.0
    currentAzimuth = currentElevation = 0.f;
    currentDelayInSamples = currentDelayTime = 0;
    currentDistance = initCoords.distance = 1.f;
    gainFactor = 1.f;
    isActive = true;
}

DelayProcessor::DelayProcessor(DelayProcessor&& other) noexcept
    : maxDelayTime(other.maxDelayTime),
    currentAzimuth(other.currentAzimuth),
    currentDelayInSamples(other.currentDelayInSamples),
    currentDelayTime(other.currentDelayTime),
    currentDistance(other.currentDistance),
    currentElevation(other.currentElevation),
    fs(other.fs),
    gainFactor(other.gainFactor),
    initCoords(other.initCoords),
    isActive(other.isActive),
    delayLine(std::move(other.delayLine)),
    delayLineLP(std::move(other.delayLineLP)),
    //delayLineTIPS(std::move(other.delayLineTIPS)),
    mirExcerpt(std::move(other.mirExcerpt)),
    position(std::move(other.position))
{

}

DelayProcessor::~DelayProcessor() {
    // anything?
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
void DelayProcessor::setDistance(float newDistance, bool forceSetDelay /* = false */)
{
    // Close distance limiter
    if (newDistance < 0.1f)
        currentDistance = 0.1f; 
    
    currentDistance = newDistance;

    // calculate new gain; actual gain handling happening in binauraliser.c, though
    // fetch gainFactor in PluginProcessor and pass on to binauraliser_setSourceGain()
    gainFactor = initCoords.distance / currentDistance;

    // Set Delay
    // watch out for potential mismatch of "fs" and host sample rate!!!
    float delayInSamples = currentDistance * (fs / SONIC_SPEED); // SONIC_SPEED defined in _common.h
    
    // original; working on delayLine member
    //setDelayTimeInSamples(delayInSamples, fs); 
    
    // force should only happen when Initial Distance is set
    setSmoothedDelayTimeInSamples(delayInSamples, fs, forceSetDelay);
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

/* original obsolete approach, replace with setSmoothedDelayTimeInSamples when it works */
void DelayProcessor::setDelayTimeInSamples(float delayTimeInSamples, double sampleRate) {
    //std::lock_guard<std::mutex> lock(delayProcessorMutex);
    
    // make currentDelayInSamples a SmoothedValue
    currentDelayInSamples = delayTimeInSamples;

    // setDelay to currentDelayInSamples.getNextValue()
    delayLine.setDelay(delayTimeInSamples);
    currentDelayTime = delayTimeInSamples / sampleRate; // in seconds
}

/* new approach, copy into setDelayTimeInSamples when it works */
void DelayProcessor::setSmoothedDelayTimeInSamples(float delayTimeInSamples, double sampleRate, bool force) {
    // set target value for SmoothedValue, force if you want to skip the ramp
    currentDelaySmoothed.setValue(delayTimeInSamples, force);
    
    // Do I have to call this here? Will produce a duplicate/concurrent call in DelayLineTIPS.process()?
    //delayLineTIPS.setDelay( currentDelaySmoothed.getNextValue());
}

void DelayProcessor::setMaxDelayTime(double maxDelayTimeInSeconds, double sampleRate) {
    delayLine.setMaximumDelayInSamples(sampleRate * maxDelayTimeInSeconds);
    delayLineLP->setMaximumDelayInSamples(sampleRate * maxDelayTimeInSeconds);
    //delayLineTIPS.setMaximumDelayInSamples(sampleRate * maxDelayTimeInSeconds);
    maxDelayTime = maxDelayTimeInSeconds;
}

void DelayProcessor::prepare(juce::dsp::ProcessSpec& spec) {
    delayLine.prepare(spec);
    setMaxDelayTime(maxDelayTime, spec.sampleRate);
    delayLineLP->prepare(spec);
    //delayLineTIPS.prepare(spec);
    convolver.reset();
    convolver.prepare(spec);
}

void DelayProcessor::process(juce::dsp::ProcessContextReplacing<float>& context) {
    //delayLine.process(context);
    delayLineLP->process(context, currentDelaySmoothed);
    //delayLineTIPS.process(context, currentDelaySmoothed);
    convolver.process(context);
}

/* This gets called in PluginProcessor::releaseResources() */
void DelayProcessor::resetDSP()
{
    delayLine.reset();
    delayLineLP.reset();
    convolver.reset();
}
