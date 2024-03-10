/*
  ==============================================================================

    DiffuseFieldProcessor.cpp
    Created: 30 Jan 2024 11:10:34am
    Author:  Micha

  ==============================================================================
*/

#include "DiffuseFieldProcessor.h"

DiffuseFieldProcessor::DiffuseFieldProcessor()
{
    dfpDelay = juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd>();
    dfpDelay.reset();
    dfpDelay.setMaximumDelayInSamples(48000); // 1 sec max delay
    dfpDelay.setDelay(0);

    dfpInitialized = false;
}

DiffuseFieldProcessor::~DiffuseFieldProcessor()
{
}

// binRev and weighting function should already have been provided by JSON import
void DiffuseFieldProcessor::init(juce::dsp::ProcessSpec& spec, float mixingTime)
{
    dfpInitialized = false;
    
    int mixingTimeInSamples = (int)((mixingTime / 1000) * spec.sampleRate); // mixing time gets passed in as milliseconds
    mixingTimeInSamples *= 2; // see synthesizeBRIR.m l.37
    mixingTimeInSamples = inverseWeightingFunc.getNumSamples(); // this seems to work better, matches Johannes' value
    
    int binRevNumSamples = binRevBuffer.getNumSamples();
    int binRevExcerptNumSamples = binRevNumSamples - mixingTimeInSamples;

    juce::AudioBuffer<float> binRevWeighted(binRevBuffer.getNumChannels(), binRevNumSamples);
    binRevWeighted.copyFrom(0, 0, binRevBuffer, 0, 0, binRevNumSamples);
    
    // beginning of binRevBuffer will be modified by wfInv values, for the later part wfInv = 1
    for (int channel = 0; channel < binRevWeighted.getNumChannels(); ++channel) {
        for (int sample = 0; sample < binRevWeighted.getNumSamples(); ++sample) {
            if (sample < mixingTimeInSamples) {
                binRevWeighted.setSample(channel, sample, binRevWeighted.getSample(channel, sample) * inverseWeightingFunc.getSample(0, sample));
            }
        }
    }
    
    // temporary buffer's ownership is moved to convolver
    convolver.loadImpulseResponse(std::move(binRevWeighted), spec.sampleRate, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::no, juce::dsp::Convolution::Normalise::no);
    convolver.reset();
    convolver.prepare(spec);
    auto irs = convolver.getCurrentIRSize(); // debug purpose

    dfpDelay.reset();
    dfpDelay.setMaximumDelayInSamples(spec.sampleRate); // 1 sec max delay
    dfpDelay.setDelay(0);
    dfpDelay.prepare(spec);

    dfpInitialized = true;
}

// inverted weighting function already applied in init()
void DiffuseFieldProcessor::process()
{
    if (dfpInitialized)
    {
        // inputBuffer has been filled prior within PluginProcessor.processBlock()
        juce::dsp::AudioBlock<float> blockToProcess = juce::dsp::AudioBlock<float>(inputBuffer);
        juce::dsp::ProcessContextReplacing<float> context(blockToProcess);
        convolver.process(context);
        dfpDelay.process(context);
    }
}
