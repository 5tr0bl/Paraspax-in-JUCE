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

    void DiffuseFieldProcessor::init(juce::dsp::ProcessSpec& spec, float mixingTime);
    void DiffuseFieldProcessor::process();

    juce::dsp::Convolution convolver;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd> dfpDelay;
    juce::AudioBuffer<float> binRevBuffer;
    juce::AudioBuffer<float> inverseWeightingFunc; // inverse wf imported from psx struct
    juce::AudioBuffer<float> inputBuffer; // this will be filled periodically in processBlock() 

    
private:
    bool dfpInitialized;
};