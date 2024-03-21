/*
  ==============================================================================

    LV_EQ.cpp
    Created: 25 May 2021 5:40:30pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "LV_SVFilter.h"

void LV_SVFilter::reset()
{
    
}
//==============================================================================

void LV_SVFilter::prepare(juce::dsp::ProcessSpec spec)
{
    mCurrentSampleRate = spec.sampleRate;
    
    mCutoff = 1000.0f;
    mQ = 0.79f;
    mGain = convertToGain(12.0f);
    mType = kBandShelf;
    mQType = kProportional;
    mRawGain = 0.0f;
    mGlobalBypass = false;
    
    mZ1.assign(spec.numChannels, 0.0);
    mZ2.assign(spec.numChannels, 0.0);
}
//==============================================================================

void LV_SVFilter::setParameter(ParameterId parameter, float parameterValue)
{
    switch (parameter) {
            
        case ParameterId::kType: mType = (FilterType)parameterValue; break;
        case ParameterId::kQType: mQType = (QType)parameterValue; break;
        case ParameterId::kCutoff: mCutoff = parameterValue; break;
        case ParameterId::kQ: mQ = parameterValue; break;
        case ParameterId::kGain: setGain(parameterValue); break;
        case ParameterId::kSampleRate: mCurrentSampleRate = parameterValue; break;
        case ParameterId::kBypass: mGlobalBypass = parameterValue; break;
    }
}
//==============================================================================

void LV_SVFilter::setGain(float value)
{
    mGain = convertToGain(value);
    mRawGain = value;
}
//==============================================================================

float LV_SVFilter::convertToGain(const float value)
{
    constexpr double inversion = 1.0 / 20.0;
    
    return pow(10, value * inversion) - 1.f;
}
//==============================================================================

float LV_SVFilter::getShelfQ(float value)
{
    if (value <= 12.0f && value >= -12.0f){
        
        return pow(10.0f, abs(value) / 80.0f) - 0.8f;
        
    } else {
        
        return 0.69f;
    }
}
//==============================================================================

float LV_SVFilter::getPeakQ(float value)
{
    // Outside of these ranges would break the DSP that controls the Q
    if (value <= 12.0f && value >= -12.0f){
        
        if (value > 0.0f){
            
            return pow(10.0f, abs(value) / 60.0f) - 0.9f;
            
        } else {
            
            return pow(10.0f, abs(value) / 45.0f) - 0.9f;
        }
        
    } else {
        
        if (value > 12.0f){
            
            return  0.79f;
            
        } else {
            
            return 0.95f;
        }
    }
}
//==============================================================================

void LV_SVFilter::process(juce::dsp::AudioBlock<float> block, const int numChannels)
{
    if (mGlobalBypass == false){
        
    float lsLevel = 0.0;
    float bsLevel = 0.0;
    float hsLevel = 0.0;
    float lpLevel = 0.0;
    float hpLevel = 0.0;
        
    switch (mType) {
            
        case kLowShelf: lsLevel = 1.0; break;
        case kBandShelf: bsLevel = 1.0; break;
        case kHighShelf: hsLevel = 1.0; break;
        case kLowPass: lpLevel = 1.0; break;
        case kHighPass: hpLevel = 1.0; break;
    }
        
    const auto numSamps = block.getNumSamples();
    //auto channelBuffers = block.getArrayOfWritePointers();
        
    const double sampleRate2X = mCurrentSampleRate * 2.0;
    const double halfSampleDuration = 1.0 / mCurrentSampleRate / 2.0;
        
    for (int sample = 0; sample < numSamps; ++sample) {
        
        // prewarp the cutoff (for bilinear-transform filters)
        double wd = mCutoff * 6.28f;
        double wa = sampleRate2X * tan(wd * halfSampleDuration);
                
        //Calculate g (gain element of integrator)
        mGCoeff = wa * halfSampleDuration;
                
        //Calculate Zavalishin's damping parameter (Q)
        switch (mQType) {

            case kParametric: mRCoeff = 1.0 - mQ; break;
            case kProportional:
                
                if (mType == kBandShelf){
                    
                    mRCoeff = 1.0 - getPeakQ(mRawGain); break;
                    
                } else {
                    
                    mRCoeff = 1.0 - getShelfQ(mRawGain); break;
                }
        }
        
        mRCoeff2 = mRCoeff * 2.0;
                
        mInversion = 1.0 / (1.0 + mRCoeff2 * mGCoeff + mGCoeff * mGCoeff);
            
        for (int ch = 0; ch < numChannels; ++ch) {
            
            const auto z1 = mZ1[ch];
            const auto z2 = mZ2[ch];
            
            float* data = block.getChannelPointer(ch);
            
            const float x = data[sample];
                
            const double HP = (x - mRCoeff2 * z1 - mGCoeff * z1 - z2) * mInversion;
            const double BP = HP * mGCoeff + z1;
            const double LP = BP * mGCoeff + z2;
            const double UBP = mRCoeff2 * BP;
            const double BShelf = x + UBP * mGain;
            const double LS = x + mGain * LP;
            const double HS = x + mGain * HP;
                
            //Main output code
            data[sample] = BShelf * bsLevel + LS * lsLevel + HS * hsLevel + HP * hpLevel + LP * lpLevel;
                
            // unit delay (state variable)
            mZ1[ch] = mGCoeff * HP + BP;
            mZ2[ch] = mGCoeff * BP + LP;
            
            }
        }
        
    } else {
        
        const auto numSamps = block.getNumSamples();
        
        for (int sample = 0; sample < numSamps; ++sample) {
            
            for (int ch = 0; ch < numChannels; ++ch) {
                
                float* data = block.getChannelPointer(ch);
                
                const float x = data[sample];
                
                data[sample] = x;
                
                }
            }
        }
}
//==============================================================================
