/*
  ==============================================================================

    XyPad.cpp
    Created: 3 Mar 2024 3:12:00am
    Author:  Micha

  ==============================================================================
*/

#include "XyPad.h"

XyPad::XyPad()
{
    addAndMakeVisible(thumb);

    // initialize callback function that syncs slider values to thumb position
    thumb.moveCallback = [&](Point<double> position) // -> void
        {
            const std::lock_guard<std::mutex> lock(vectorMutex);
            const auto bounds = getLocalBounds().toDouble();
            const auto w = static_cast<double> (thumbSize); // thumb width/height

            for (auto* slider : xSliders)
            {
                slider->setValue(jmap(position.getX(), 0.0, bounds.getWidth() - w, slider->getMinimum(), slider->getMaximum()));
            }
            for (auto* slider : ySliders)
            {
                slider->setValue(jmap(position.getY(), 0.0, bounds.getHeight() - w, slider->getMinimum(), slider->getMaximum()));
            }
        };
}

void XyPad::resized()
{
    thumb.setBounds(getLocalBounds().withSizeKeepingCentre(thumbSize, thumbSize));
}

void XyPad::paint(Graphics& g)
{
    g.setColour(Colours::black);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 10.f);
}

/**
*   slider is a raw Pointer to the respective slider in the PluginEditor
*/
void XyPad::registerSlider(Slider* slider, Axis axis)
{
    const std::lock_guard<std::mutex> lock(vectorMutex); // local, gets destructed at the end of this method
    
    if (axis == Axis::X)
        xSliders.push_back(slider);
    if (axis == Axis::Y)
        ySliders.push_back(slider);
}

void XyPad::deregisterSlider(Slider* slider)
{
    const std::lock_guard<std::mutex> lock(vectorMutex); // local, gets destructed at the end of this method
    
    // remove first sorts the requested slider(s) to the end of the vector, then returns an iterator to its position(s)
    // erase then erases from that starting point till the end of the vector
    xSliders.erase(std::remove(xSliders.begin(), xSliders.end(), slider), xSliders.end());
    ySliders.erase(std::remove(ySliders.begin(), ySliders.end(), slider), ySliders.end());
}

XyPad::Thumb::Thumb()
{
    // Thumb should stay on the XY Pad screen
    constrainer.setMinimumOnscreenAmounts(thumbSize, thumbSize, thumbSize, thumbSize);
}

void XyPad::Thumb::paint(Graphics& g)
{
    g.setColour(Colours::white);
    g.fillEllipse(getLocalBounds().toFloat());
}

void XyPad::Thumb::mouseDown(const MouseEvent& event)
{
    dragger.startDraggingComponent(this, event); // pass the mouse event to the thumb instance
}

void XyPad::Thumb::mouseDrag(const MouseEvent& event)
{
    dragger.dragComponent(this, event, &constrainer);
    if (moveCallback)
        moveCallback(getPosition().toDouble());
}
