/*
  ==============================================================================

    ComponentProps.cpp
    Created: 14 May 2021 9:07:19pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void MarauderAudioProcessorEditor::setShadowProps()
{
    shadowProperties.radius = 8;
    shadowProperties.offset = juce::Point<int> (-1, 3);
    dialShadow.setShadowProperties (shadowProperties);
}

void MarauderAudioProcessorEditor::setCommonVerticalSliderProps(juce::Slider& slider)
{
    slider.setColour(0x1001200, juce::Colour::fromFloatRGBA(0, 0, 0, 0.25f));
    slider.setColour(0x1001300, juce::Colours::whitesmoke.darker());
    slider.setColour(0x1001310, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 0.65));
    slider.setColour(0x1001311, juce::Colour::fromFloatRGBA(0, 0, 0, 0.5));
    slider.setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25));
    slider.setColour(0x1001700, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    slider.setColour(0x1001500, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 128, 32);
    slider.setDoubleClickReturnValue(true, 0.0);
    slider.setComponentEffect(&dialShadow);
    addAndMakeVisible(slider);
}

void MarauderAudioProcessorEditor::setCommonSliderProps(juce::Slider& slider)
{
    slider.setColour(0x1001200, juce::Colour::fromFloatRGBA(0, 0, 0, 0.25f));
    slider.setColour(0x1001300, juce::Colours::whitesmoke.darker());
    slider.setColour(0x1001310, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 0.65));
    slider.setColour(0x1001311, juce::Colours::lightgoldenrodyellow.darker(0.2f));
    slider.setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25));
    slider.setColour(0x1001700, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    slider.setColour(0x1001500, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    slider.setTextValueSuffix(" dB");
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 128, 32);
    slider.setDoubleClickReturnValue(true, 0.0);
    slider.setComponentEffect(&dialShadow);
    addAndMakeVisible(slider);
}

void MarauderAudioProcessorEditor::setCommonLabelProps(juce::Label &label)
{
    addAndMakeVisible(&label);
    label.setJustificationType(juce::Justification::centredTop);
    label.setColour(0x1000280, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    label.setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.5));
    label.setColour(0x1000282, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
}

void MarauderAudioProcessorEditor::setCommonButtonProps(juce::TextButton &button)
{
    addAndMakeVisible(&button);
    button.setColour(0x1000100, juce::Colours::whitesmoke.darker(1.0).withAlpha(1.0f));
    button.setColour(0x1000c00, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    button.setColour(0x1000101, juce::Colours::lightgoldenrodyellow.darker(0.2f));
    button.setColour(0x1000102, juce::Colours::black.brighter(0.1));
    button.setColour(0x1000103, juce::Colours::black.brighter(0.1));
}

void MarauderAudioProcessorEditor::setAllProps()
{
    // Set all common slider properties
    for (int i = 0; i < verticalSliders.size(); ++i) {
        
        setCommonVerticalSliderProps(*verticalSliders[i]);
    }
    
    for (int i = 0; i < sliders.size(); ++i) {
        
        setCommonSliderProps(*sliders[i]);
    }
    
    // Set all common label properties
    for (int i = 0; i < outLabels.size(); ++i) {
        
        setCommonLabelProps(*outLabels[i]);
        outLabels[i]->attachToComponent(verticalSliders[i], false);
        outLabels[i]->setText(outLabelTexts[i], juce::dontSendNotification);
    }
    
    for (int i = 0; i < filterLabels.size(); ++i) {
        
        setCommonLabelProps(*filterLabels[i]);
        filterLabels[i]->setText(filterLabelsTexts[i], juce::dontSendNotification);
        filterLabels[i]->attachToComponent(sliders[i], false);
    }
    
    // Set all common button properties
    for (int i = 0; i < buttons.size(); ++i) {
        
        setCommonButtonProps(*buttons[i]);
    }
}
