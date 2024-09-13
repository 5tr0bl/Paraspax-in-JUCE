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
    roomDims = std::make_unique<Vector3D<float>>(0, 0, 0);
    
    addAndMakeVisible(thumb);
    addAndMakeVisible(srcThumb);

    // initialize callback function that syncs slider values to thumb position
    thumb.moveCallback = [&](Point<double> position) // -> void
        {
            const std::lock_guard<std::mutex> lock(vectorMutex);
            const auto bounds = getLocalBounds().toDouble();
            const auto w = static_cast<double> (thumbSize); // thumb width/height
            xSliders[0]->setValue(jmap(position.getX(), 0.0, bounds.getWidth() - w, xSliders[0]->getMinimum(), xSliders[0]->getMaximum()));
            ySliders[0]->setValue(jmap(bounds.getHeight() - position.getY(), 0.0, bounds.getHeight() - w, ySliders[0]->getMinimum(), ySliders[0]->getMaximum()));
        };
    srcThumb.moveCallback = [&](Point<double> position) // -> void
        {
            const std::lock_guard<std::mutex> lock(vectorMutex);
            const auto bounds = getLocalBounds().toDouble();
            const auto w = static_cast<double> (thumbSize); // thumb width/height
            xSliders[1]->setValue(jmap(position.getX(), 0.0, bounds.getWidth() - w, xSliders[0]->getMinimum(), xSliders[0]->getMaximum()));
            ySliders[1]->setValue(jmap(bounds.getHeight() - position.getY(), 0.0, bounds.getHeight() - w, ySliders[0]->getMinimum(), ySliders[0]->getMaximum()));
        };
}

void XyPad::resized()
{
    thumb.setBounds(getLocalBounds().withSizeKeepingCentre(thumbSize, thumbSize));
    srcThumb.setBounds(getLocalBounds().withSize(thumbSize, thumbSize));

    /* If you closed the Editor window and open it again, the thumbs' positions get reset on the XY Pad, prevent that! 
       //Calling the sliderValueChanged methods this way here can theoretically pick the wrong slider, at least so the video guy says...
    if (!xSliders.empty())
        sliderValueChanged(xSliders[0]); 
    if (!ySliders.empty())
        sliderValueChanged(ySliders[0]);
    */
}

void XyPad::paint(Graphics& g)
{
    g.setColour(Colours::black);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 10.f);
}

void XyPad::setRoomDimensions(const Vector3D<float>& newDimensions)
{
    roomDims->x = newDimensions.x;
    roomDims->y = newDimensions.y;
    roomDims->z = newDimensions.z;

    // step width for the sliders, depending on room dimensions
    auto bounds = getLocalBounds();
    float xSliderInterval = newDimensions.x / bounds.getWidth();
    float ySliderInterval = newDimensions.y / bounds.getHeight();

    // Adjust slider ranges for x & y
    for (auto* slx : xSliders)
        slx->setRange(0, roomDims->x, xSliderInterval);
    for (auto* sly : ySliders)
        sly->setRange(0, roomDims->y, ySliderInterval);
}

/* this should preferrably be only called once upon psx loading... */
void XyPad::setThumbPosition(String thumbName, const Vector3D<float>& newPosition)
{
    // scale real position to the boundaries of the xyPad
    auto bounds = getLocalBounds();
    float xScalingFactor = bounds.getWidth() / roomDims->x;
    float yScalingFactor = bounds.getHeight() / roomDims->y;

    // flip y coord on vertical axis
    if (thumbName == "receiver") {
        thumb.setCentrePosition(newPosition.x * xScalingFactor,
                                bounds.getHeight() - (newPosition.y * yScalingFactor));
        xSliders[0]->setValue(newPosition.x);
        ySliders[0]->setValue(newPosition.y);
    }
    else if (thumbName == "source") {
        srcThumb.setCentrePosition(newPosition.x * xScalingFactor,
                                   bounds.getHeight() - (newPosition.y * yScalingFactor));
        xSliders[1]->setValue(newPosition.x);
        ySliders[1]->setValue(newPosition.y);
    }
}

/**
*   slider is a raw Pointer to the respective slider in the PluginEditor
*/
void XyPad::registerSlider(Slider* slider, Axis axis)
{
    slider->addListener(this);
    const std::lock_guard<std::mutex> lock(vectorMutex); // local, gets destructed at the end of this method
    
    if (axis == Axis::X)
        xSliders.push_back(slider);
    if (axis == Axis::Y)
        ySliders.push_back(slider);
}

void XyPad::deregisterSlider(Slider* slider)
{
    slider->removeListener(this);
    const std::lock_guard<std::mutex> lock(vectorMutex); // local, gets destructed at the end of this method
    
    // remove first sorts the requested slider(s) to the end of the vector, then returns an iterator to its position(s)
    // erase then erases from that starting point till the end of the vector
    xSliders.erase(std::remove(xSliders.begin(), xSliders.end(), slider), xSliders.end());
    ySliders.erase(std::remove(ySliders.begin(), ySliders.end(), slider), ySliders.end());
}

void XyPad::sliderValueChanged(Slider* slider)
{
    // Avoid Loopback (redundantly repeated call)
    if (thumb.isMouseOverOrDragging(false) || srcThumb.isMouseOverOrDragging(false))
        return;

    // x slider or y slider?
    const auto isXAxisSLider = std::find(xSliders.begin(), xSliders.end(), slider) != xSliders.end();
    const auto bounds = getLocalBounds().toDouble();
    const auto w = static_cast<double>(thumbSize);
    
    // Check if the slider is in the xSliders vector and update the respective thumb
    auto it = std::find(xSliders.begin(), xSliders.end(), slider);
    if (it != xSliders.end())
    {
        int index = std::distance(xSliders.begin(), it);
        if (index == 0) // The first slider is for 'thumb'
        {
            thumb.setTopLeftPosition(jmap(slider->getValue(), slider->getMinimum(), slider->getMaximum(), 0.0, bounds.getWidth() - w), thumb.getY());
        }
        else if (index == 1) // The second slider is for 'srcThumb'
        {
            srcThumb.setTopLeftPosition(jmap(slider->getValue(), slider->getMinimum(), slider->getMaximum(), 0.0, bounds.getWidth() - w), srcThumb.getY());
        }
    }

    // Check if the slider is in the ySliders vector and update the respective thumb
    it = std::find(ySliders.begin(), ySliders.end(), slider);
    if (it != ySliders.end())
    {
        int index = std::distance(ySliders.begin(), it);
        if (index == 0) // The first slider is for 'thumb'
        {
            thumb.setTopLeftPosition(thumb.getX(), jmap(slider->getValue(), slider->getMinimum(), slider->getMaximum(), bounds.getHeight() - w, 0.0));
        }
        else if (index == 1) // The second slider is for 'srcThumb'
        {
            srcThumb.setTopLeftPosition(srcThumb.getX(), jmap(slider->getValue(), slider->getMinimum(), slider->getMaximum(), bounds.getHeight() - w, 0.0));
        }
    }
    
    repaint();
}

XyPad::Thumb::Thumb() : thumbColour(juce::Colours::white), displayedChar(" ")
{
    constrainer.setMinimumOnscreenAmounts(thumbSize, thumbSize, thumbSize, thumbSize);
}

XyPad::Thumb::Thumb(juce::Colour colour, juce::String displayChar) : thumbColour(colour), displayedChar(displayChar)
{
    // Thumb should stay on the XY Pad screen
    constrainer.setMinimumOnscreenAmounts(thumbSize, thumbSize, thumbSize, thumbSize);
}

void XyPad::Thumb::paint(Graphics& g)
{
    // Thumb
    g.setColour(thumbColour);
    g.fillEllipse(getLocalBounds().toFloat());

    // Text
    g.setColour(juce::Colours::black);
    g.setFont(thumbSize / 1.5f); // Set font size

    // Calculate the position to center the text inside the ellipse
    auto bounds = getLocalBounds().toFloat();
    auto textWidth = g.getCurrentFont().getStringWidthFloat(displayedChar);
    auto textHeight = g.getCurrentFont().getHeight();
    float x = bounds.getCentreX() - (textWidth / 2.0f);
    float y = bounds.getCentreY() - (textHeight / 2.0f);

    // Draw the text
    g.drawText(displayedChar, x, y, textWidth, textHeight, juce::Justification::centred);
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

XyPad::DummyThumb::DummyThumb()
{
    // Thumb should stay on the XY Pad screen
    constrainer.setMinimumOnscreenAmounts(thumbSize, thumbSize, thumbSize, thumbSize);
}

void XyPad::DummyThumb::paint(Graphics& g)
{
    g.setColour(Colours::red);
    g.fillEllipse(getLocalBounds().toFloat());
}
