/*
  ==============================================================================

    LV_Label.h
    Created: 1 Aug 2021 1:17:17am
    Author:  landon viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace juce
{

class LV_Label : public Label
{
public:
    
    LV_Label()
    {
        setJustificationType(juce::Justification::centredTop);
        setColour(0x1000280, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
        setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25));
        setColour(0x1000282, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    }
    
private:
    
};
}
