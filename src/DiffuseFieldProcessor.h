/*
  ==============================================================================

    Binaural Noise needed here;

    Monaural RIR needed for piecewise convolution

    It is crucial that the Binaural Noise in the psx struct is based on the same 
    SOFA data, that is being imported in the Plugin!

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "_common.h"
#include "DelayLineLP.h"
#include "DelayLineTIPS.h"
#include "saf.h"                /* Main include header for SAF */
#include "saf_externals.h"      /* To also include SAF dependencies (cblas etc.) */

class DiffuseFieldProcessor {

public:
    DiffuseFieldProcessor();
    ~DiffuseFieldProcessor();

    void DiffuseFieldProcessor::init(juce::dsp::ProcessSpec& spec, float mixingTime, float sampleRate);
    void DiffuseFieldProcessor::process(juce::AudioBuffer<float>& outputBuffer);
    void DiffuseFieldProcessor::saveAudioBufferAsJsonStereo(const juce::AudioBuffer<float>& buffer, const juce::String& fileName);
    void DiffuseFieldProcessor::saveAudioBufferAsJSON(const juce::AudioBuffer<float>& buffer, const juce::String& fileName);

    bool DiffuseFieldProcessor::isInitialized();
    void DiffuseFieldProcessor::setDelay(float newDelay);
    void DiffuseFieldProcessor::setSmoothedDelayTimeInSamples(float delayTimeInSamples, double sampleRate, bool force);
    void DiffuseFieldProcessor::setDelayByDistance(float distance);

    juce::dsp::Convolution convolver;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd> dfpDelay;
    std::unique_ptr<DelayLineLP> delayLineLP;
    DelayLineTIPS dfpDelayTIPS;
    SmoothedValue<double, ValueSmoothingTypes::Linear> currentDelaySmoothed;
    juce::AudioBuffer<float> binRevBuffer;
    juce::AudioBuffer<float> inverseWeightingFunc; // inverse wf imported from psx struct
    juce::AudioBuffer<float> inputBuffer; // this will be filled periodically in processBlock() 

private:
    float bnfLatency = 1536.f; // 12 * HOP_SIZE given by binauraliser.c;
    float delay;
    float fs;
    bool dfpInitialized;

    std::mutex diffuseFieldProcessorMutex;
};