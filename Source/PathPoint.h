/*
  ==============================================================================

    PathPoint.h
    Created: 17 Jun 2020 8:24:57pm
    Author:  Zack Sussman

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PathPoint    : public Component
{
public:
    PathPoint(float opacity = 1.f,double size = 2);
    ~PathPoint();

    void paint (Graphics&) override;
    void resized() override;

private:
    Colour colour;
    double size;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PathPoint)
};
