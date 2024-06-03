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
#include "DelayLineTIPS.h"
#include "DelayLineLP.h"

class DelayProcessor {
public:
    DelayProcessor::DelayProcessor();
    DelayProcessor::DelayProcessor(double maxDelayTimeInSeconds, double sampleRate);
    DelayProcessor(DelayProcessor&& other) noexcept; // Move constructor
    DelayProcessor(const DelayProcessor&) = delete;  // Delete the Copy Constructor
    DelayProcessor::~DelayProcessor();

    void DelayProcessor::setPosition(float newX, float newY, float newZ);
    void DelayProcessor::setPosition(const juce::Vector3D<float>& newPos);
    void DelayProcessor::setDistance(float newDistance, bool forceSetDelay = false);
    void DelayProcessor::setRirExcerpt(const juce::AudioBuffer<float>& rir, int mirStartIndex, int mirEndIndex, juce::dsp::ProcessSpec& spec);
    void DelayProcessor::setDelayTimeInSamples(float delayTimeInSamples, double sampleRate);
    void DelayProcessor::setSmoothedDelayTimeInSamples(float delayTimeInSamples, double sampleRate, bool force);
    void DelayProcessor::setMaxDelayTime(double maxDelayTimeInSeconds, double sampleRate);
    void DelayProcessor::prepare(juce::dsp::ProcessSpec& spec);
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

    float DelayProcessor::getCurrentDistance() const
    {
        return currentDistance;
    }

    void DelayProcessor::setInitialDistance(float newDistance)
    {
        jassert(newDistance >= 0.1f);
        initCoords.distance = newDistance;
        // reset current distance, force new delay value in setSmoothedDelay function
        setDistance(initCoords.distance, /*forceDelay = */true);
    }

    void setAzimuth(float azimuth) {
        currentAzimuth = azimuth;
    }

    void DelayProcessor::setInitialAzimuth(float azimuth) {
        initCoords.azimuth = azimuth;
        setAzimuth(azimuth);
    }

    float getAzimuth() {
        return currentAzimuth;
    }

    void setElevation(float elevation) {
        currentElevation = elevation;
    }

    void DelayProcessor::setInitialElevation(float elevation) {
        initCoords.elevation = elevation;
        setElevation(elevation);
    }

    float getElevation() {
        return currentElevation;
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
    SmoothedValue<double, ValueSmoothingTypes::Linear> currentDelaySmoothed;

    struct {
        float azimuth, elevation, distance, x, y, z;
    } initCoords; 

private:
    double maxDelayTime;
    double currentDelayTime; // in seconds
    float currentDelayInSamples;

    float currentDistance, gainFactor, fs;
    float currentAzimuth, currentElevation;

    bool isActive;

    std::mutex delayProcessorMutex;

    juce::dsp::Convolution convolver;
    juce::AudioBuffer<float> mirExcerpt;

    std::unique_ptr<DelayLineLP> delayLineLP;
    //DelayLineLP delayLineLP;
    DelayLineTIPS delayLineTIPS;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd> delayLine;
};