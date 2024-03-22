

#include "../PluginEditor.h"

void MarauderAudioProcessorEditor::uiConstructor()
{
    // Window
    initWindow();
    addAndMakeVisible(windowComponent);
    
    // Initialize shadows
    setShadowProps();
    initShadows();
    
    // Initialize component properties
    setAllProps();
    
    // Sliders
    resampleSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, resampleId, resampleSlider);
    resampleSlider.setRange(100.0, 44100.0, 1.0);
    resampleSlider.setSkewFactorFromMidPoint(6000.0);
    resampleSlider.setTextValueSuffix(" Hz");
    resampleSlider.setLookAndFeel(&customDial);
    resampleSlider.setComponentEffect(&dialShadow);

    bitDepthSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, bitDepthId, bitDepthSlider);
    bitDepthSlider.setRange(6.0, 16.0, 1.0);
    bitDepthSlider.setTextValueSuffix(" Bits");
    bitDepthSlider.setLookAndFeel(&customDial);
    bitDepthSlider.setComponentEffect(&dialShadow);

    noiseSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, noiseId, noiseSlider);
    noiseSlider.setRange(0.0, 16.0, 0.25);
    noiseSlider.setTextValueSuffix(" dB");
    noiseSlider.setLookAndFeel(&customDial2);
    noiseSlider.setComponentEffect(&dialShadow);

    mixSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, mixId, mixSlider);
    mixSlider.setRange(0.0, 100.0, 1.0);
    mixSlider.setTextValueSuffix(" %");
    mixSlider.setLookAndFeel(&customDial2);
    mixSlider.setComponentEffect(&dialShadow);
    
    highCutSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, highCutId, highCutSlider);
    highCutSlider.setRange(40.0, 500.0, 1.0);
    highCutSlider.setSkewFactorFromMidPoint(100.0);
    highCutSlider.setLookAndFeel(&customDial3);
    highCutSlider.setComponentEffect(&dialShadow);

    // Out Sliders
    driveSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, driveSliderId, driveSlider);
    driveSlider.setRange(0.0f, 12.0f, 0.5);
    driveSlider.setLookAndFeel(&customFader);
    driveSlider.setColour(0x1001300, juce::Colours::whitesmoke.darker(1.0f).darker(1.0f));
    driveSlider.setComponentEffect(&sliderShadow);
    
    trimSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    trimSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, trimSliderId, trimSlider);
    trimSlider.setRange(-24.0, 24.0, 1.0);
    trimSlider.setLookAndFeel(&customFader);
    trimSlider.setColour(0x1001300, juce::Colours::whitesmoke.darker(1.0f).darker(1.0f));
    trimSlider.setComponentEffect(&sliderShadow);
    
    // Buttons
    phaseToggle.setButtonText("Phase");
    phaseToggle.setClickingTogglesState(true);
    phaseToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, phaseId, phaseToggle);
    
    resetToggle.setButtonText("Reset");
    resetToggle.addListener(this);
    
    jitterToggle.setButtonText("Jitter");
    jitterToggle.setClickingTogglesState(true);
    jitterToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, jitterId, jitterToggle);
}
