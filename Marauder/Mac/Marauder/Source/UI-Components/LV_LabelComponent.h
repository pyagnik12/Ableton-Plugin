

#pragma once

#include <JuceHeader.h>
#include "../Widgets/LV_Label.h"

//==============================================================================
/*
*/
class LV_LabelComponent  : public juce::Component
{
public:
    LV_LabelComponent(juce::String name, juce::Component &component);
    ~LV_LabelComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::LV_Label label;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_LabelComponent)
};
