/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ViatorDial.h"
#include "./UI-Components/LV_Window.h"
#include "./Widgets/StyleSheet.h"

//==============================================================================
/**
*/
class MarauderAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Slider::Listener, juce::Button::Listener
{
public:
    MarauderAudioProcessorEditor (MarauderAudioProcessor&);
    ~MarauderAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;

private:
    
    // Shadow
    void setShadowProps();
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
    // Logo
    juce::Image mLogo;
    
    // Background
    juce::Image pluginBackground;

    
    // Output Sliders
    void setCommonVerticalSliderProps(juce::Slider& slider);
    
    juce::Slider driveSlider, trimSlider;
    std::vector<juce::Slider*> verticalSliders {&driveSlider, &trimSlider};
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach, trimSliderAttach;
    
    // Output Labels
    void setCommonLabelProps(juce::Label& label);
    
    juce::Label driveLabel, trimLabel;
    std::vector<juce::Label*> outLabels {&driveLabel, &trimLabel};
    std::vector<std::string> outLabelTexts {"Drive", "Trim"};
    
    // Sliders
    void setCommonSliderProps(juce::Slider& slider);
    juce::LV_FaderLAF customFader;
    
    juce::Slider resampleSlider, bitDepthSlider, mixSlider, noiseSlider, highCutSlider;
    std::vector<juce::Slider*> sliders {&resampleSlider, &bitDepthSlider, &mixSlider, &noiseSlider, &highCutSlider};
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> resampleSliderAttach, bitDepthSliderAttach, mixSliderAttach, noiseSliderAttach, highCutSliderAttach;
    
    // Filter Labels
    juce::Label bandOneGainLabel, bandTwoGainLabel, bandThreeGainLabel, bandFourGainLabel, highCutLabel;
    std::vector<juce::Label*> filterLabels {&bandOneGainLabel, &bandTwoGainLabel, &bandThreeGainLabel, &bandFourGainLabel, &highCutLabel};
    std::vector<std::string> filterLabelsTexts {"Resample", "Bit Depth", "Mix", "Noise", "Filter"};
    
    // Buttons
    void setCommonButtonProps(juce::TextButton& button);
    juce::TextButton resetToggle, phaseToggle, jitterToggle;
    std::vector<juce::TextButton*> buttons {&resetToggle, &phaseToggle, &jitterToggle};
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> resetToggleAttach, phaseToggleAttach, jitterToggleAttach;

    // Set all component properties
    void setAllProps();
    
    void setFlexBox();
    
    // Window border
    juce::GroupComponent windowBorder;
    
    // Shadow button
    juce::ToggleButton shadowToggle;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> shadowToggleAttach;
        
    // Custom dial look and feel
    ViatorDial customDial;
    ViatorDial2 customDial2;
    ViatorDial3 customDial3;
    
    // Menu box
    juce::ComboBox mSampleMenu;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> mSampleMenuAttach;
    
    // Hyperlink button
    juce::HyperlinkButton mWebLink;
    juce::URL mWebUrl {"https://www.patreon.com/ViatorDSP"};
    
    /** UI Methods ================================================================*/
    void uiConstructor();
    void uiPaint();
    void uiResized(float width, float height);
    
    /** Window ====================================================================*/
    LV_Window windowComponent;
    
    void initWindow();
    void saveWindowSize();
    bool constructorFinished {false};
    
    /** Fader shadow ===========================================================*/
    juce::DropShadow sliderShadowProperties;
    juce::DropShadowEffect sliderShadow;
    void initShadows();
    
    MarauderAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MarauderAudioProcessorEditor)
};
