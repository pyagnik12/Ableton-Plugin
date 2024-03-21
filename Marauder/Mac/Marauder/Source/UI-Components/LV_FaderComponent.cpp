#include <JuceHeader.h>
#include "LV_FaderComponent.h"

//==============================================================================
LV_FaderComponent::LV_FaderComponent(juce::String suffix,
                                     double rangeStart,
                                     double rangeEnd,
                                     double intervalValue,
                                     double returnValue,
                                     juce::AudioProcessorValueTreeState& tree,
                                     juce::String parameter)
{
    initShadows();
    initAttach(tree, parameter);
    initProps(suffix, rangeStart, rangeEnd, intervalValue, returnValue);
}

LV_FaderComponent::~LV_FaderComponent()
{
    slider.setLookAndFeel(nullptr);
    slider.setComponentEffect(nullptr);
}

void LV_FaderComponent::paint (juce::Graphics& g)
{

}

void LV_FaderComponent::resized()
{
    slider.setBounds(getLocalBounds());
}

void LV_FaderComponent::initShadows()
{
    sliderShadowProperties.radius = 8;
    sliderShadowProperties.offset = juce::Point<int> (0, 0);
    sliderShadowProperties.colour = juce::Colours::black.withAlpha(1.0f);
    sliderShadow.setShadowProperties (sliderShadowProperties);
}

void LV_FaderComponent::initAttach(juce::AudioProcessorValueTreeState& tree, juce::String parameter)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    sliderAttach = std::make_unique<SliderAttachment>(tree, parameter, slider);
}

void LV_FaderComponent::initProps(juce::String suffix, double rangeStart, double rangeEnd, double intervalValue, double returnValue)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 72, 32);
    slider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black.withAlpha(0.35f));
    slider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::black.withAlpha(0.0f));
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black.withAlpha(0.0f));
    slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke.withAlpha(0.25f));
    slider.setRange(rangeStart, rangeEnd, intervalValue);
    slider.setDoubleClickReturnValue(true, returnValue);
    slider.setTextValueSuffix(suffix);
    slider.setLookAndFeel(&customFader);
    slider.setComponentEffect(&sliderShadow);
    addAndMakeVisible(slider);
}
