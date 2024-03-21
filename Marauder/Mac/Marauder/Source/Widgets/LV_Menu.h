/*
  ==============================================================================

    LV_Menu.h
    Created: 10 Oct 2021 1:42:17pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace juce
{

    class LV_Menu : public ComboBox
    {
        
    public:
    
        LV_Menu()
        {
            setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::black.brighter(0.1f));
            setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::black);
            setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, juce::Colours::black.withAlpha(0.5f));
            setColour(juce::ComboBox::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
            setColour(juce::ComboBox::ColourIds::arrowColourId, juce::Colours::skyblue.darker(0.5f));

            getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, juce::Colours::black.brighter(0.1f));
            getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colours::skyblue.withAlpha(0.1f));
            getLookAndFeel().setColour(juce::PopupMenu::textColourId, juce::Colours::whitesmoke.withAlpha(0.5f));
            getLookAndFeel().setColour(juce::PopupMenu::highlightedTextColourId, juce::Colours::skyblue);
        
            setJustificationType(juce::Justification::centred);
        }
    };
}
