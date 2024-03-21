/*
  ==============================================================================

    LV_GroupComponent.h
    Created: 24 Oct 2021 1:01:25am
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Widgets/LV_GroupComponent.h"

//==============================================================================
/*
*/
class LV_GroupComponent  : public juce::Component
{
public:
    LV_GroupComponent(juce::String text);
    ~LV_GroupComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::LV_GroupComponent titleBorder;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_GroupComponent)
};
