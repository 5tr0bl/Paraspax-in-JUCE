/*
  ==============================================================================

    XyPad.h
    Created: 3 Mar 2024 3:12:00am
    Author:  Micha
    Based on: https://www.youtube.com/watch?v=6aRu9RKkx8E

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class XyPad : public Component
{
public:
    enum class Axis { X, Y };

    class Thumb : public Component
    {
        public:
            Thumb();
            void paint(Graphics& g) override;
            void mouseDown(const MouseEvent& event) override;
            void mouseDrag(const MouseEvent& event) override;
            
            // a function that returns void and accepts a Point (the thumbs' x,y-position)
            std::function<void(Point<double>)> moveCallback;
        private:
            ComponentDragger dragger;
            ComponentBoundsConstrainer constrainer;
            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Thumb)
    };

    XyPad();
    void resized() override;
    void paint(Graphics& g) override;
    void registerSlider(Slider* slider, Axis axis);
    void deregisterSlider(Slider* slider);

private:
    std::vector<Slider*> xSliders, ySliders;
    Thumb thumb;

    std::mutex vectorMutex; // A Lock to prevent registering and deregistering sliders at the same time

    static constexpr int thumbSize = 30;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XyPad)
};