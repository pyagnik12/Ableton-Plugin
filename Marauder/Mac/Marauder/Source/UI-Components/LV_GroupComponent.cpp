/*
  ==============================================================================

    LV_GroupComponent.cpp
    Created: 24 Oct 2021 1:01:25am
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LV_GroupComponent.h"

//==============================================================================
LV_GroupComponent::LV_GroupComponent(juce::String text)
{
    addAndMakeVisible(titleBorder);
    titleBorder.setText(text);
}

LV_GroupComponent::~LV_GroupComponent()
{
}

void LV_GroupComponent::paint (juce::Graphics& g)
{
}

void LV_GroupComponent::resized()
{
    titleBorder.setBounds(getLocalBounds());
}
