/*
  ==============================================================================

    DelayProcessor.h
    Created: 10 Oct 2023 10:55:01am
    Author:  Micha

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "_common.h"
//#include "DelayLineBase.h"

class DelayProcessor {
public:
    DelayProcessor::DelayProcessor();
    DelayProcessor::DelayProcessor(double maxDelayTimeInSeconds, double sampleRate);
    DelayProcessor(DelayProcessor&& other) noexcept; // Move constructor
    DelayProcessor(const DelayProcessor&) = delete;  // Delete the Copy Constructor
    DelayProcessor::~DelayProcessor();

    void DelayProcessor::setPosition(float newX, float newY, float newZ);
    void DelayProcessor::setPosition(const juce::Vector3D<float>& newPos);
    void DelayProcessor::setDistance(float newDistance);
    void DelayProcessor::setRirExcerpt(const juce::AudioBuffer<float>& rir, int mirStartIndex, int mirEndIndex, juce::dsp::ProcessSpec& spec);
    void DelayProcessor::setDelayTimeInSamples(float delayTimeInSamples, double sampleRate);
    void DelayProcessor::setMaxDelayTime(double maxDelayTimeInSeconds, double sampleRate);
    void DelayProcessor::prepare(juce::dsp::ProcessSpec& spec);
    void processBlock(juce::dsp::AudioBlock<float>& block);
    void DelayProcessor::process(juce::dsp::ProcessContextReplacing<float>& context);

    double getDelayTime() const {
        return currentDelayTime;
    }

    float getDelayTimeInSamples(double sampleRate) const {
        return currentDelayInSamples;
    }

    float DelayProcessor::getGainFactor() const
    {
        return gainFactor;
    }

    float DelayProcessor::getDistance() const
    {
        return distance;
    }

    void setAzimuth(float newValue) {
        azimuth = newValue;
    }

    float getAzimuth() {
        return azimuth;
    }

    void setElevation(float newValue) {
        elevation = newValue;
    }

    float getElevation() {
        return elevation;
    }

    void setIsActive(bool newValue) {
        isActive = newValue;
    }

    bool getIsActive() {
        return isActive;
    }

    //juce::dsp::ProcessorDuplicator<dsp::FIR::Filter<float>, dsp::FIR::Coefficients<float>> filter;
    //bool convolutionEnabled = true;

    juce::Vector3D<float> position;

private:
    double maxDelayTime;
    float currentDelayInSamples;
    double currentDelayTime; // in seconds

    float distance, gainFactor, fs;
    float azimuth, elevation;

    bool isActive;

    juce::dsp::Convolution convolver;
    juce::AudioBuffer<float> mirExcerpt;

    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd> delayLine;
};