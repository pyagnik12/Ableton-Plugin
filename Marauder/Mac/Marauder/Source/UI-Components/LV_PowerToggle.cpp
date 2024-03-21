/*
  ==============================================================================

    LV_PowerToggle.cpp
    Created: 24 Oct 2021 7:39:06pm
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LV_PowerToggle.h"

//==============================================================================
LV_PowerToggle::LV_PowerToggle()
{
    addAndMakeVisible(powerToggle);
    powerToggle.setLookAndFeel(&customPowerToggle);
}

LV_PowerToggle::~LV_PowerToggle()
{
    powerToggle.setLookAndFeel(nullptr);
}

void LV_PowerToggle::paint (juce::Graphics& g)
{

}

void LV_PowerToggle::resized()
{
    powerToggle.setBounds(getLocalBounds());
}

void LV_PowerToggle::setColour(int colourID, juce::Colour newColour)
{
    powerToggle.setColour(colourID, newColour);
}
