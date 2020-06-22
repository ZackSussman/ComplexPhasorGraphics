/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include <cmath>
#include <iostream>

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.

    setFramesPerSecond(frameRate); // This sets the frequency of the update calls.
   
    
    for (int i = 0; i < numberOfPathPoints; i++) {
        float alpha = 1- (i*1.0)/numberOfPathPoints;
        pathPoints.emplace_back(new PathPoint(alpha, 2));
    }
    
    tailLengthSlider.setRange(0, 0.5, 0.01);
    tailLengthSlider.setValue(0);
    

    setSize(800, 600);
    
    for (int i = 0; i < pathPoints.size(); i++) {
        addAndMakeVisible(*pathPoints[i]);
        pathPoints[i] -> setBounds(getLocalBounds());
    }
  
    
    for (int i = 0; i < pathPoints.size(); i++) {
        (*pathPoints[i]).setSize(getWidth(), getHeight());
        (*pathPoints[i]).setTopLeftPosition((*pathPoints[0]).getX() + .5*xShift, (*pathPoints[0]).getY());
    }
    curve->clear();
    curve->startNewSubPath(getWidth()/2 + xShift, getHeight()/2);
    

    addAndMakeVisible(startStopButton);
    addAndMakeVisible(xPhaserRadiusSlider);
    addAndMakeVisible(yPhaserRadiusSlider);
    addAndMakeVisible(xPhaserRadiusLabel);
    addAndMakeVisible(yPhaserRadiusLabel);
    addAndMakeVisible(xFrequencySlider);
    addAndMakeVisible(xFrequencyLabel);
    addAndMakeVisible(yFrequencyLabel);
    addAndMakeVisible(yFrequencySlider);
    addAndMakeVisible(tailLengthSlider);
    addAndMakeVisible(tailLengthLabel);
    addAndMakeVisible(resetButton);
    resetButton.setButtonText("Reset");
    addAndMakeVisible(toggleCurveButton);
    toggleCurveButton.setButtonText("Path");
    
    
    tailLengthSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    tailLengthLabel.setText("Tail Length", dontSendNotification);
    
    
    
    xPhaserRadiusSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    xPhaserRadiusLabel.setText("Horizontal Radius", dontSendNotification);

    
    yPhaserRadiusSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    yPhaserRadiusLabel.setText("Vertical Radius", dontSendNotification);
    
    xFrequencySlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    xFrequencyLabel.setText("Horizontal Frequency", dontSendNotification);
    
    yFrequencySlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    yFrequencyLabel.setText("Vertical Frequency", dontSendNotification);
    
    
    
    startStopButton.setToggleState(true, dontSendNotification);

    
    xPhaserRadiusSlider.setRange(-1, 1, 0.002);
    yPhaserRadiusSlider.setRange(-1, 1, 0.002);
    
    xFrequencySlider.setRange(0, 3, 0.01);
    yFrequencySlider.setRange(0, 3, 0.01);
    


    
    xPhaserRadiusSlider.setValue(1);
    yPhaserRadiusSlider.setValue(1);
    
    xFrequencySlider.setValue(1);
    yFrequencySlider.setValue(1);
    
   
    
    
    time = 0;
    
}


MainComponent::~MainComponent()
{
    delete curve;
}

void MainComponent::clearCurve()
{
    curve->clear();
    curve->startNewSubPath(getWidth()/2 + pathPoints[pathPoints.size() - 1]->getX(), getHeight()/2 + pathPoints[pathPoints.size() - 1]->getY());
}

//==============================================================================
void MainComponent::update()
{
    // This function is called at the frequency specified by the setFramesPerSecond() call
    // in the constructor. You can use it to update counters, animate values, etc.
    
    if (!toggleCurveButton.getToggleState()) {
        curve->clear();
    }
    
    if (sliderValues[0] != xPhaserRadiusSlider.getValue()) {
        clearCurve();
        time = 0;
    }
    if (sliderValues[1] != yPhaserRadiusSlider.getValue()) {
         clearCurve();
        time = 0;
    }
    if (sliderValues[2] != xFrequencySlider.getValue()) {
        clearCurve();
        time = 0;
    }
    if (sliderValues[3] != yFrequencySlider.getValue()) {
         clearCurve();
        time = 0;
    }
    
    sliderValues[0] = xPhaserRadiusSlider.getValue();
    sliderValues[1] = yPhaserRadiusSlider.getValue();
    sliderValues[2] = xFrequencySlider.getValue();
    sliderValues[3] = yFrequencySlider.getValue();
    
    
    if (resetButton.isDown()) {
        xPhaserRadiusSlider.setValue(1);
        yPhaserRadiusSlider.setValue(1);
        xFrequencySlider.setValue(1);
        yFrequencySlider.setValue(1);
        time = 0;
        startStopButton.setToggleState(false, dontSendNotification);
        tailLengthSlider.setValue(0);
        
        
        for (int i = 0; i < pathPoints.size(); i++) {
            addAndMakeVisible(*pathPoints[i]);
            pathPoints[i] -> setBounds(getLocalBounds());
        }
        
        
        for (int i = 0; i < pathPoints.size(); i++) {
            (*pathPoints[i]).setSize(getWidth(), getHeight());
            (*pathPoints[i]).setTopLeftPosition((*pathPoints[0]).getX() + .5*xShift, (*pathPoints[0]).getY());
        }
    
         clearCurve();
    }
    
    
    
    double xFreq = xFrequencySlider.getValue();
    double yFreq = yFrequencySlider.getValue();
    double xRad = axisScale*xPhaserRadiusSlider.getValue();
    double yRad = axisScale*yPhaserRadiusSlider.getValue();
  
    if (startStopButton.getToggleState()) {
        startStopButton.setButtonText("Pause");
    }
    else {
        startStopButton.setButtonText("Play");
    }
    
    
    if (startStopButton.getToggleState()) {
        enteredPausedState = false;
        for (int i = 0; i < pathPoints.size(); i++) {
                (*pathPoints[i]).setTopLeftPosition(xShift + xRad*cos((time - tailLengthSlider.getValue()*(3.14*i)/pathPoints.size())*xFreq*6.28), yRad*sin((time - tailLengthSlider.getValue()*(3.14*i)/pathPoints.size())*yFreq*6.28));
             
        }
        
        time -= 1.0/frameRate;
        
    }
    
    else {
       /*
        for (int i = 0; i < pathPoints.size(); i++) {
            (*pathPoints[i]).setTopLeftPosition(pathPoints[pathPoints.size()-1]->getX(), pathPoints[pathPoints.size()-1]->getY());
        }
        */
        
        if (!enteredPausedState) {
            pausedCycle = 0;
            enteredPausedState = true;
            nonPausedCatchupTime = tailLengthSlider.getValue()*3.14*(pathPoints.size()-1)/(pathPoints.size());
        }
        
        for (int i = 0; i < pathPoints.size(); i++) {
            (*pathPoints[i]).setTopLeftPosition(xShift + xRad*cos((time - (1-((1.0*pausedCycle)/nonPausedCatchupTime))*tailLengthSlider.getValue()*(3.14*i)/pathPoints.size())*xFreq*6.28), yRad*sin((time - tailLengthSlider.getValue()*(3.14*i)/pathPoints.size())*yFreq*6.28));
            
        }
        
        pausedCycle += 1.0/frameRate;
        
        
    }
    
    if (toggleCurveButton.getToggleState() && time < -15.0/frameRate) {
        double endX = getWidth()/2 + xShift + xRad*cos((time)*xFreq*6.28);
        double endY = getHeight()/2 + yRad*sin((time)*yFreq*6.28);
        curve->lineTo(endX, endY);
    }
    else {
        clearCurve();
    }

    
}

bool MainComponent::arePointsWithinRange(double pointOne, double pointTwo, double range) {
    
    if (pointOne*pointTwo < 0) {
        return false;
    }
    
    bool distance = sqrt(abs(pointOne*pointOne - pointTwo*pointTwo));
    return distance <= range;
}
//==============================================================================
void MainComponent::paint (Graphics& g)
{

    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);
    g.setColour(Colours::grey);
    g.drawLine(getWidth()/2 - axisScale*xPhaserRadiusSlider.getValue() + xShift, getHeight()/2, getWidth()/2 + axisScale*xPhaserRadiusSlider.getValue() + xShift, getHeight()/2);
    
    g.drawLine(getWidth()/2 + xShift, getHeight()/2 - axisScale*yPhaserRadiusSlider.getValue(), getWidth()/2 + xShift, getHeight()/2 + axisScale*yPhaserRadiusSlider.getValue());

    g.strokePath(*curve, PathStrokeType(.5));
    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    startStopButton.setBounds(getLocalBounds());
    toggleCurveButton.setBounds(getLocalBounds());
    
    xPhaserRadiusLabel.attachToComponent(&xPhaserRadiusSlider, false);
    xPhaserRadiusSlider.setBounds(0, 2.5*getHeight()/30, getWidth()/5, getHeight()/30);
    
    xFrequencyLabel.attachToComponent(&xFrequencySlider, false);
    xFrequencySlider.setBounds(0, 4.5*getHeight()/15, getWidth()/5, getHeight()/30);
    
    yFrequencyLabel.attachToComponent(&yFrequencySlider, false);
    yFrequencySlider.setBounds(0, 6*getHeight()/15, getWidth()/5, getHeight()/30);
    
    
    yPhaserRadiusLabel.attachToComponent(&yPhaserRadiusSlider, false);
    yPhaserRadiusSlider.setBounds(0, 3*getHeight()/15, getWidth()/5, getHeight()/30);

    tailLengthLabel.attachToComponent(&tailLengthSlider, false);
    tailLengthSlider.setBounds(0, 9*getHeight()/15, getWidth()/5, getHeight()/30);
    
    resetButton.setSize(getWidth()/5, getHeight()/30);
    resetButton.setTopLeftPosition(0, 12*getHeight()/15);
    
    toggleCurveButton.setSize(getWidth()/5, getHeight()/30);
    toggleCurveButton.setTopLeftPosition(0, 10*getHeight()/15);
    
    
 
    for (int i = 0; i < pathPoints.size(); i++) {
        (*pathPoints[i]).setSize(getWidth(), getHeight());
        (*pathPoints[i]).setTopLeftPosition(getWidth()/2 + xShift, getHeight()/2);
    }
}
