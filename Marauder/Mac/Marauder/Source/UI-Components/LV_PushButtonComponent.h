/*
  ==============================================================================

    LV_PushButtonComponent.h
    Created: 24 Oct 2021 8:30:24pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Widgets/LV_PushButton.h"

//==============================================================================
/*
*/
class LV_PushButtonComponent  : public juce::Component
{
public:
    LV_PushButtonComponent(juce::String buttonText);
    ~LV_PushButtonComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::LV_PushButton pushButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_PushButtonComponent)
};
