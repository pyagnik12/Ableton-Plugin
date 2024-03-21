/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MarauderAudioProcessorEditor::MarauderAudioProcessorEditor (MarauderAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    uiConstructor();
}

MarauderAudioProcessorEditor::~MarauderAudioProcessorEditor()
{
    verticalSliders.reserve(0);
    sliders.reserve(0);

    outLabels.reserve(0);
    filterLabels.resize(0);
    buttons.reserve(0);
    
    // This fixes a memory leak when you close the window
    for (auto i = 0; i < verticalSliders.size(); ++i) {
        
        verticalSliders[i]->setLookAndFeel(nullptr);
    }
    
    for (auto i = 0; i < sliders.size(); ++i) {
        
        sliders[i]->setLookAndFeel(nullptr);
    }
}

//==============================================================================
void MarauderAudioProcessorEditor::paint (juce::Graphics& g)
{
    
}

void MarauderAudioProcessorEditor::resized()
{
    // Helpful vars
    auto width = getWidth();
    auto height = getHeight();
        
    uiResized(width, height);
}

void MarauderAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    
}

void MarauderAudioProcessorEditor::buttonClicked(juce::Button *button)
{
    if (button == &resetToggle){
        
        resampleSlider.setValue(44100);
        bitDepthSlider.setValue(16);
        mixSlider.setValue(100);
        noiseSlider.setValue(0.0);
        highCutSlider.setValue(50);
        phaseToggle.setToggleState(false, juce::dontSendNotification);
        jitterToggle.setToggleState(false, juce::dontSendNotification);
        driveSlider.setValue(0.0);
        trimSlider.setValue(0.0);
    }
}

void MarauderAudioProcessorEditor::initShadows()
{
    sliderShadowProperties.radius = 8;
    sliderShadowProperties.offset = juce::Point<int> (0, 0);
    sliderShadowProperties.colour = juce::Colours::black.withAlpha(1.0f);
    sliderShadow.setShadowProperties (sliderShadowProperties);
}
