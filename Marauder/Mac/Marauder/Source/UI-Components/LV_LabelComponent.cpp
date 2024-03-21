/*
  ==============================================================================

    LV_LabelComponent.cpp
    Created: 24 Oct 2021 1:13:14am
    Author:  Landon Viator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LV_LabelComponent.h"

//==============================================================================
LV_LabelComponent::LV_LabelComponent(juce::String name, juce::Component &component)
{
    addAndMakeVisible(label);
    label.setText(name, juce::dontSendNotification);
    label.attachToComponent(&component, false);
}

LV_LabelComponent::~LV_LabelComponent()
{
}

void LV_LabelComponent::paint (juce::Graphics& g)
{
}

void LV_LabelComponent::resized()
{
}
