/*
  ==============================================================================

    OriginModule.cpp
    Created: 11 May 2021 9:21:11am
    Author:  Landon Viator

  ==============================================================================
*/

#include "LV_BitCrusher.h"

void LV_BitCrusher::prepare(juce::dsp::ProcessSpec& spec)
{
    bitRateRange = juce::NormalisableRange<float>(1.0f, 450.0f, 0.1f, 0.2f);
    
    currentSampleRate = spec.sampleRate;

    mBitDepth = 16;
    mResampledRate = 44100.0f;
    mMix = 100.0f;
    mPreampGain = 0.0f;
    mJitter = 0.0f;
    mNoiseGain = 0.0f;
    rawDrive = 0.0f;
}

void LV_BitCrusher::render(juce::dsp::AudioBlock<float> block, const int numChannels)
{
    // Set cutoff and Jitter
    setResampledRate(mResampledRate + (currentSampleRate - mResampledRate) * (mJitter * 0.01f));
    
    const auto numSamps = block.getNumSamples();
    
    for (int ch = 0; ch < numChannels; ++ch)
    {
        float* data = block.getChannelPointer(ch);
        
        for (int sample = 0; sample < numSamps; ++sample)
        {
            //Dry signal
            float drySpl = data[sample];
            
            // Reduce bit depth
            float totalQLevels = std::powf(2, mBitDepth);
            
            // Add pink noise and have the bit depth influence it
            auto pinkNoise = getPinkNoise();
            
            // Multiply the pink noise between 0 and 1 with a smoothed gain range
            auto pinkNoiseScaled = pinkNoise * juce::jmap(pow(10.0f, mNoiseGain / 20.0f), 1.0f, 6.3f, 0.0f, 0.05f);
            
            // Add pink noise before quantization
            float val = data[sample] + pinkNoiseScaled;
            
            // Add Dithering
            float remainder = std::fmodf(val, 1 / totalQLevels * juce::jmap(mNoiseGain, 0.0f, 16.0f, 24.0f, 12.0f));
            
            // Quantize
            data[sample] = val - remainder;
            
            if (rateDivide > 1)
            {
                if (sample % int(rateDivide) != 0)
                {
                    data[sample] = data[sample - sample % int(rateDivide + pinkNoise * mJitter)];
                }
            }
            
            // Half wave to full wave rectifier
            if (data[sample] < 0)
            {
                // Rectification
                data[sample] *= mPreampGain;
                
                // Soft clip
                data[sample] = std::atan(data[sample] * std::powf(10.0, rawDrive * 0.05));
                
                // Gain compensation
                data[sample] *= std::pow(10.0, -rawDrive * 0.033333);
            }
            
            // Mix logic
            data[sample] = (drySpl * (1.0f - setMix(mMix)) + data[sample] * setMix(mMix));
        }
    }
}
    
void LV_BitCrusher::setParameter(ParameterId parameter, float parameterValue)
{
    switch (parameter)
    {
        case ParameterId::kPreamp:
        {
            mPreampGain = juce::jmap(parameterValue, 0.0f, 12.0f, 1.0f, -1.0f);
            rawDrive = juce::jmap(parameterValue, 0.0f, 12.0f, 0.0f, 18.0f);
            break;
        }
            
        case ParameterId::kResampledRate: mResampledRate = parameterValue; break;
        case ParameterId::kBitDepth: mBitDepth = parameterValue; break;
        case ParameterId::kMix: mMix = parameterValue; break;
        case ParameterId::kJitter: mJitter = parameterValue; break;
        case ParameterId::kNoiseGain: mNoiseGain = parameterValue; break;
        case ParameterId::kSampleRate: currentSampleRate = parameterValue; break;
    }
}

void LV_BitCrusher::setResampledRate(int value)
{
    // Reverse range to make more sense to the user.
    auto tempValue = juce::jmap<float>(value, 0.0f, currentSampleRate, 51.0f, 0.0f);
    rateDivide = bitRateRange.convertFrom0to1(tempValue / 100.0f);
}
    
float LV_BitCrusher::setMix(float value)
{
    jassert(juce::isPositiveAndNotGreaterThan(value, 100.0f));
    return value / 100.0f;
}

float LV_BitCrusher::getPinkNoise()
{
    float white = whiteNoise.nextFloat() - 0.5f;
    
    float b0 = 0.99765 + white * 0.0990460;
    float b1 = 0.96300 + white * 0.2965164;
    float b2 = 0.57000 + white * 1.0526913;
    float pink = b0 + b1 + b2 + white * 0.1848;
    
    return pink;
}


