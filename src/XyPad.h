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

class XyPad : public Component, Slider::Listener
{
public:
    enum class Axis { X, Y };

    class Thumb : public Component
    {
    public:
        Thumb();
        Thumb(juce::Colour colour, juce::String displayChar);
        void paint(Graphics& g) override;
        void mouseDown(const MouseEvent& event) override;
        void mouseDrag(const MouseEvent& event) override;

        // a function that returns void and accepts a Point (the thumbs' x,y-position)
        std::function<void(Point<double>)> moveCallback;
    private:
        juce::Colour thumbColour;
        ComponentDragger dragger;
        ComponentBoundsConstrainer constrainer;
        String displayedChar;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Thumb)
    };

    // originally used for source thumb
    class DummyThumb : public Component
    {
    public:
        DummyThumb();
        void paint(Graphics& g) override;
    private:
        ComponentDragger dragger;
        ComponentBoundsConstrainer constrainer;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DummyThumb)
    };

    XyPad();
    void resized() override;
    void paint(Graphics& g) override;
    void setRoomDimensions(const Vector3D<float>& newDimensions);
    void setThumbPosition(String thumbName, const Vector3D<float>& newPosition);
    void registerSlider(Slider* slider, Axis axis);
    void deregisterSlider(Slider* slider);

    std::unique_ptr<Vector3D<float>> roomDims;

private:
    void sliderValueChanged(Slider* slider) override;

    std::vector<Slider*> xSliders, ySliders;
    Thumb thumb{ juce::Colours::white, "L" };
    Thumb srcThumb{ juce::Colours::red, "S"};
    
    std::mutex vectorMutex; // A Lock to prevent registering and deregistering sliders at the same time

    static constexpr int thumbSize = 15;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XyPad)
};