

#include <JuceHeader.h>
#include "LV_Window.h"

//==============================================================================
LV_Window::LV_Window()
{
}

LV_Window::~LV_Window()
{
}

void LV_Window::paint (juce::Graphics& g)
{
    // Paint UI components
    paintBackground(g);

}

void LV_Window::resized()
{
}

void LV_Window::paintBackground(juce::Graphics &g)
{
    //Image layer from Illustrator
    
    // Draw and position the image
}

void LV_Window::paintLogoAndLink(juce::Graphics &g)
{
    // Logo layer
    
    // Draw and position the image
    
    // Patreon link
}

void LV_Window::paintText(juce::Graphics &g)
{
    // Plugin text

}

void LV_Window::setWidthAndHeight(float w, float h)
{
    width = w;
    height = h;
}
