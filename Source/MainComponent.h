/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PathPoint.h"
#include <vector>
#include <memory>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AnimatedAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void update() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    void clearCurve();
    bool arePointsWithinRange(double pointOne, double pointTwo, double range);

private:
    //==============================================================================
    // Your private member variables go here...
    
    double time;
    
    const int axisScale = 50*5;
    const int xShift = 40;
    const int frameRate = 60;
    const int numberOfPathPoints = 300;
    
    
    ToggleButton startStopButton;
    
    ToggleButton toggleCurveButton;
   
    Slider xPhaserRadiusSlider;
    Label xPhaserRadiusLabel;
    
    Slider tailLengthSlider;
    Label tailLengthLabel;
   
    Slider yPhaserRadiusSlider;
    Label yPhaserRadiusLabel;
    
    double sliderValues[4];
    
    Slider xFrequencySlider;
    Label xFrequencyLabel;
    
    Slider yFrequencySlider;
    Label yFrequencyLabel;
    
    
    TextButton resetButton;
    
    bool enteredPausedState = false;
    double stopTime;
    double nonPausedCatchupTime;
    double pausedCycle = 0;
    
    bool doneWithTrailSlideIn = false;
    
    std::vector <std::unique_ptr<PathPoint>> pathPoints;
    
    double initialTailLength;
    
    Path* curve = new Path();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent);
};
