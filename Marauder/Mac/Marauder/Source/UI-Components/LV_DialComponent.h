/*
  ==============================================================================

    LV_DialComponent.h
    Created: 24 Oct 2021 12:17:36am
    Author:  Landon Viator
 
    The last arg for the dial style is 1-3, you can also set the colors for each with the
    usual calls.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Widgets/LV_Dial.h"
#include "../Widgets/StyleSheet.h"

//==============================================================================
/*
*/
class LV_DialComponent  : public juce::Slider
{
public:
    LV_DialComponent(juce::String suffix,
                     double rangeStart,
                     double rangeEnd,
                     double intervalValue,
                     double returnValue,
                     juce::AudioProcessorValueTreeState& tree,
                     juce::String parameter);
    
    ~LV_DialComponent() override;

    enum class DialStyle
    {
        kHardDial,
        kAlphaDial,
        kAbleDial
    };
    
    void setDialStyle(DialStyle dialStyle);
    void setColour(int colourID, juce::Colour newColour);
    void enableShadow(bool enable);

private:
    
    /** Slider ================================================================*/
    juce::Slider dial;
    juce::LV_HardDialLAF hardDial;
    juce::LV_AlphaDialLAF alphaDial;
    juce::LV_CustomAbleDialLAF ableDial {false};
    
    /** Attachment ============================================================*/
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> dialAttach;
    
    /** Methods ================================================================*/
    void paint (juce::Graphics&) override;
    void resized() override;
    void initAttach(juce::AudioProcessorValueTreeState& tree, juce::String parameter);
    void initProps(juce::String suffix,
                   double rangeStart,
                   double rangeEnd,
                   double intervalValue,
                   double returnValue);
    
    /** Fader shadow ===========================================================*/
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    void initShadows();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_DialComponent)
};
