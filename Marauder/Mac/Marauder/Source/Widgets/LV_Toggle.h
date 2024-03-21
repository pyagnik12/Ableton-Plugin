/*
  ==============================================================================

    LV_Toggle.h
    Created: 21 Aug 2021 2:06:36am
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace juce
{

    class LV_Toggle : public TextButton
    {
        
    public:
    
        LV_Toggle()
        {
            setClickingTogglesState(true);
            setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::black.withAlpha(0.35f));
            setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::black.withAlpha(0.35f));
            setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::skyblue.withAlpha(0.75f));
            setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::skyblue.withAlpha(0.75f));
            setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
        } 
    };
}
