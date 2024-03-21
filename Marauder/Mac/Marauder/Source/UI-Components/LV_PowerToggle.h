/*
  ==============================================================================

    LV_PowerToggle.h
    Created: 24 Oct 2021 7:39:06pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Widgets/StyleSheet.h"

//==============================================================================
/*
*/
class LV_PowerToggle  : public juce::Component
{
public:
    LV_PowerToggle();
    ~LV_PowerToggle() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setColour(int colourID, juce::Colour newColour);

private:
    
    /** Toggles ================================================================*/
    juce::ToggleButton powerToggle;
    juce::LV_CustomPowerToggleLAF customPowerToggle;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_PowerToggle)
};
