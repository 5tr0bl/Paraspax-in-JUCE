/*
  ==============================================================================

    Attempt to build a DelayLine with two read pointers

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

template <typename Type>
class DualDelayLine : public juce::dsp::DelayLine<Type>
{
public:
    DualDelayLine() : juce::dsp::DelayLine<Type>() {}
    ~DualDelayLine() {}

private:
    //SmoothedValue<float> crossFader(1.0f);
};