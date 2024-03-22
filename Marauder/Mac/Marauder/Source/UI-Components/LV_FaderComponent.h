

#pragma once

#include <JuceHeader.h>
#include "../Widgets/LV_Fader.h"
#include "../Widgets/StyleSheet.h"

//==============================================================================
/*
*/
class LV_FaderComponent  : public juce::Slider
{
public:
    LV_FaderComponent(
                      juce::String suffix,
                      double rangeStart,
                      double rangeEnd,
                      double intervalValue,
                      double returnValue,
                      juce::AudioProcessorValueTreeState& tree,
                      juce::String parameter);
    
    ~LV_FaderComponent() override;
    
private:
    
    /** Slider ================================================================*/
    juce::Slider slider;
    juce::LV_FaderLAF customFader;
    
    /** Attachment ============================================================*/
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> sliderAttach;
    
    /** Methods ===============================================================*/
    void paint (juce::Graphics&) override;
    void resized() override;
    void initAttach(juce::AudioProcessorValueTreeState& tree, juce::String parameter);
    void initProps(juce::String suffix,
                   double rangeStart,
                   double rangeEnd,
                   double intervalValue,
                   double returnValue);
    
    /** Fader shadow ===========================================================*/
    juce::DropShadow sliderShadowProperties;
    juce::DropShadowEffect sliderShadow;
    void initShadows();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_FaderComponent)
};
