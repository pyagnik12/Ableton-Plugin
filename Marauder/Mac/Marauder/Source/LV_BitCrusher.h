/*
  ==============================================================================

    OriginModule.h
    Created: 11 May 2021 9:21:11am
    Author:  Landon Viator

  ==============================================================================
*/

#ifndef LV_BitCrusher_hpp
#define LV_BitCrusher_hpp

#include "JuceHeader.h"

class LV_BitCrusher
{
public:
    void prepare(juce::dsp::ProcessSpec& spec);
    
    void render(juce::dsp::AudioBlock<float> block, const int numChannels);
    
    enum class ParameterId
    {
        kPreamp,
        kResampledRate,
        kBitDepth,
        kMix,
        kJitter,
        kNoiseGain,
        kSampleRate,
    };
    
    void setParameter(ParameterId parameter, float parameterValue);

    
private:
    
    void setResampledRate(int value);
    float setMix(float value);
    float getPinkNoise();
    
    float mPreampGain;
    float mResampledRate;
    float mBitDepth;
    float mMix;
    float mJitter;
    float mNoiseGain;
    float output;
    float currentSampleRate;
    float rawDrive;
    
    int mFilterType;
    int rateDivide;
    
    juce::NormalisableRange<float> bitRateRange;
    
    juce::Random whiteNoise;
};

#endif /* LV_BitCrusher_hpp */
