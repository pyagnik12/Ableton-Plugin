/*
  ==============================================================================

    LV_MenuComponent.h
    Created: 24 Oct 2021 1:28:03am
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Widgets/LV_Menu.h"

//==============================================================================
/*
*/
class LV_MenuComponent  : public juce::Component
{
public:
    LV_MenuComponent(juce::String defaultText);
    ~LV_MenuComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void addItem(const juce::String &newItemText, int newItemId);

private:
    
    juce::LV_Menu menu;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_MenuComponent)
};
