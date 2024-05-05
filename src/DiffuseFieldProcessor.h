/*
  ==============================================================================

    Binaural Noise needed here;

    Monaural RIR needed for piecewise convolution
    -- map output to Stereo
    -- how to acquire MIR



  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "_common.h"

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
    void DiffuseFieldProcessor::setDelayByDistance(float distance);

    juce::dsp::Convolution convolver;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd> dfpDelay;
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