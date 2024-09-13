/*
  ==============================================================================

    DelayLineLP.h
    Created: 14 May 2024 2:00:00pm
    Author:  Micha

    This is an alternative/extended approach to the DelayLineTIPS Class
    Here, a lowpass filter smoothing of the delay time is desired

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "_common.h"

class DelayLineLP : public juce::dsp::DelayLine<double, juce::dsp::DelayLineInterpolationTypes::Lagrange3rd>
{
public:
    DelayLineLP() {};
    ~DelayLineLP() {};

    /* Move constructor */
    DelayLineLP(DelayLineLP&& other) noexcept : lowpassFilter(std::move(other.lowpassFilter))
    {

    }

    void initFilter(double sampleRate)
    {
        lowpassFilter = std::make_unique<juce::dsp::IIR::Filter<double>>();
        lowpassFilter->coefficients = juce::dsp::IIR::Coefficients<double>::makeLowPass(sampleRate, cutoffFreq, resonance);
    }

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

        // Handle deviating sample rate values !!!!!!

        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            auto* inputSamples = inputBlock.getChannelPointer(channel);
            auto* outputSamples = outputBlock.getChannelPointer(channel);

            for (size_t i = 0; i < numSamples; ++i)
            {
                // Get next smoothed delay time
                double nextDelayTime = smoothedDelayInSamples.getNextValue();

                // Apply lowpass filtering to delay time
                double filteredDelayTime = lowpassFilter->processSample(nextDelayTime);

                // Set the delay time
                setDelay(filteredDelayTime);

                // Process samples
                pushSample((int)channel, inputSamples[i]);
                outputSamples[i] = popSample((int)channel);
            }
        }
    }

private:
    double resonance = 0.4;
    double defaultSampleRate = 48000;
    double cutoffFreq = SMOOTHING_PARAM_FREQ;  // defined in _common.h
    std::unique_ptr<juce::dsp::IIR::Filter<double>> lowpassFilter;
    
};