/*
  ==============================================================================

    LV_Window.h
    Created: 23 Oct 2021 12:53:38am
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LV_Window  : public juce::Component
{
public:
    LV_Window();
    ~LV_Window() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setWidthAndHeight(float w, float h);
    
private:

    /** Image background ======================================================*/
    juce::Image pluginBackground;
    void paintBackground(juce::Graphics &g);
    
    /** Logo and Link =========================================================*/
    juce::Image footerLogo;
    juce::HyperlinkButton mWebLink;
    juce::URL mWebUrl {"https://www.patreon.com/ViatorDSP"};
    void paintLogoAndLink(juce::Graphics &g);
    
    /** Text ==================================================================*/
    void paintText(juce::Graphics &g);
    
    /** Vars ==================================================================*/
    float width {0.0f};
    float height {0.0f};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LV_Window)
};
