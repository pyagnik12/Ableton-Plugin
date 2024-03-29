

#include <JuceHeader.h>
#include "LV_PushButtonComponent.h"

//==============================================================================
LV_PushButtonComponent::LV_PushButtonComponent(juce::String buttonText)
{
    addAndMakeVisible(pushButton);
    pushButton.setButtonText(buttonText);
}

LV_PushButtonComponent::~LV_PushButtonComponent()
{
}

void LV_PushButtonComponent::paint (juce::Graphics& g)
{

}

void LV_PushButtonComponent::resized()
{
    pushButton.setBounds(getLocalBounds());
}
