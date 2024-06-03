/*
  ==============================================================================

    DelayLineTIPS.h
    Created: 7 May 2024 12:30:51am
    Author:  Micha

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/* TIPS = time interpolated per sample */
class DelayLineTIPS : public juce::dsp::DelayLine<double, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd>
{
public:
    DelayLineTIPS() {};
    ~DelayLineTIPS() {};

    template <typename ProcessContext>
    void process(const ProcessContext& context, SmoothedValue<double, ValueSmoothingTypes::Linear>& smoothedDelayInSamples)
    {
        const auto& inputBlock = context.getInputBlock();
        auto& outputBlock = context.getOutputBlock();
        const auto numChannels = outputBlock.getNumChannels();
        const auto numSamples = outputBlock.getNumSamples();

        jassert(inputBlock.getNumChannels() == numChannels);
        //jassert(inputBlock.getNumChannels() == writePos.size());
        jassert(inputBlock.getNumSamples() == numSamples);

        if (context.isBypassed)
        {
            outputBlock.copyFrom(inputBlock);
            return;
        }

        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            auto* inputSamples = inputBlock.getChannelPointer(channel);
            auto* outputSamples = outputBlock.getChannelPointer(channel);

            for (size_t i = 0; i < numSamples; ++i)
            {
                // adjust time here
                setDelay(smoothedDelayInSamples.getNextValue());
                pushSample((int)channel, inputSamples[i]);
                outputSamples[i] = popSample((int)channel);
            }
        }
    };
};