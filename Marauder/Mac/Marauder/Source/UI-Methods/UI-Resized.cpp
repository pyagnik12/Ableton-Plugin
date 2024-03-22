

#include "../PluginEditor.h"

void MarauderAudioProcessorEditor::uiResized(float width, float height)
{
    // Plugin background UI
    windowComponent.setWidthAndHeight(width, height);
    windowComponent.setBounds(getLocalBounds());
    
    // Helpful vars
    float leftMargin = width * 0.1;
    float topMargin = height * 0.12;
    float smallDialSize = width * 0.1;
    float dialSize = width * 0.13;
    float sliderHeight = height * 0.57;
    float spaceBetween = 1.08;
    float dialSpaceBetween = 1.2;
    
    resetToggle.setBounds(leftMargin * 1.25, topMargin, leftMargin, leftMargin / 2.0);
    phaseToggle.setBounds(resetToggle.getX(), resetToggle.getY() + resetToggle.getHeight() * spaceBetween, resetToggle.getWidth(), resetToggle.getHeight());
    jitterToggle.setBounds(phaseToggle.getX(), phaseToggle.getY() + phaseToggle.getHeight() * spaceBetween, phaseToggle.getWidth(), phaseToggle.getHeight());
    highCutSlider.setBounds(jitterToggle.getX(), jitterToggle.getY() + jitterToggle.getHeight() * 1.75, smallDialSize, smallDialSize);
    
    resampleSlider.setBounds(resetToggle.getX() + resetToggle.getWidth() * 2.0, topMargin * 1.4, dialSize, dialSize);
    noiseSlider.setBounds(resampleSlider.getX(), resampleSlider.getY() + resampleSlider.getHeight() * dialSpaceBetween, dialSize, dialSize);
    bitDepthSlider.setBounds(resampleSlider.getX() + resampleSlider.getWidth() * 1.5, resampleSlider.getY(), dialSize, dialSize);
    mixSlider.setBounds(bitDepthSlider.getX(), noiseSlider.getY(), dialSize, dialSize);
    
    driveSlider.setBounds(bitDepthSlider.getX() + bitDepthSlider.getWidth() * 1.25, bitDepthSlider.getY(), dialSize, sliderHeight);
    trimSlider.setBounds(driveSlider.getX() + driveSlider.getWidth(), driveSlider.getY(), driveSlider.getWidth(), driveSlider.getHeight());
    
    // Save plugin size in the tree
    saveWindowSize();
}
