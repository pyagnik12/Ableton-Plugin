/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LV_BitCrusher.h"
#include "LV_SVFIlter.h"

// Sliders
#define driveSliderId "drive"
#define driveSliderName "Drive"
#define trimSliderId "trim"
#define trimSliderName "Trim"

// Buttons
#define phaseId "phase"
#define phaseName "Phase"
#define jitterId "jitter"
#define jitterName "Jitter"
#define menuId "menu"
#define menuName "Menu"

// Dials
#define highCutId "filter"
#define highCutName "Filter"
#define resampleId "resample"
#define resampleName "Resample"
#define bitDepthId "bit depth"
#define bitDepthName "Bit Depth"
#define noiseId "noise"
#define noiseName "Noise"
#define mixId "mix"
#define mixName "Mix"
//==============================================================================
/**
*/
class MarauderAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    MarauderAudioProcessor();
    ~MarauderAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // Value tree
    juce::AudioProcessorValueTreeState treeState;
    juce::ValueTree variableTree
    { "Variables", {},
      {
        { "Group", {{ "name", "Vars" }},
          {
              { "Parameter", {{ "id", "width" }, { "value", 0.0 }}},
                { "Parameter", {{ "id", "height" }, { "value", 0.0 }}},
          }
        }
      }
    };
    
    /** Window Vars =====================================================*/
    float windowWidth {0.0f};
    float windowHeight {0.0f};
    
private:
    
    // Variables
    float lastSampleRate, projectSampleRate;
    
    float lastTrimGain, currentTrimGain;
    
    float currentDrive = 0.0;
    
    int currentPhase;
    
    bool oversamplingToggle;
    
    // My functions
    void setPhase(bool phase);
    
    void callProcessorCore(juce::dsp::AudioBlock<float> block, const int numChannels);
    
    void setAllSampleRates(float value);
    
    // Parameter function
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    // Parameter listener function
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    
    // dsp modules
    LV_BitCrusher bitCrusherModule;
    LV_SVFilter hpFilter;
    juce::dsp::Bias<float> biasModule;
    
    juce::dsp::Oversampling<float> oversamplingProcessor;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MarauderAudioProcessor)
};
