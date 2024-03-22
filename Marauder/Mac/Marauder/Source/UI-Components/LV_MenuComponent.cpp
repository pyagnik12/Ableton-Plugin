
#include <JuceHeader.h>
#include "LV_MenuComponent.h"

//==============================================================================
LV_MenuComponent::LV_MenuComponent(juce::String defaultText)
{
    addAndMakeVisible(menu);
    menu.setTextWhenNothingSelected(defaultText);
    menu.setTextWhenNoChoicesAvailable(defaultText);
}

LV_MenuComponent::~LV_MenuComponent()
{
}

void LV_MenuComponent::paint (juce::Graphics& g)
{

}

void LV_MenuComponent::resized()
{
    menu.setBounds(getLocalBounds());
}

void LV_MenuComponent::addItem(const juce::String &newItemText, int newItemId)
{
    menu.addItem(newItemText, newItemId);
}
