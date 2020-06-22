/*
  ==============================================================================

    PathPoint.cpp
    Created: 17 Jun 2020 8:24:57pm
    Author:  Zack Sussman

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PathPoint.h"

//==============================================================================
PathPoint::PathPoint(float opacity, double passedSize)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    colour = Colour(100*(1-opacity),(1-opacity*opacity)*255, 255*(opacity*opacity)).withAlpha(1-opacity*opacity);
    size = passedSize;
}




PathPoint::~PathPoint()
{
}

void PathPoint::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.setColour(colour);
    g.drawEllipse(Rectangle<float>(getWidth()/2, getHeight()/2, size, size), size);
}

void PathPoint::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
