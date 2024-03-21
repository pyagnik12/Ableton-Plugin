/*
  ==============================================================================

    Filters.cpp
    Created: 26 May 2021 8:11:22pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginProcessor.h"

void MarauderAudioProcessor::setAllSampleRates(float value)
{
    mLSFilter.setParameter(LV_SVFilter::ParameterId::kSampleRate, value);
    mBPFilter1.setParameter(LV_SVFilter::ParameterId::kSampleRate, value);
    mBPFilter2.setParameter(LV_SVFilter::ParameterId::kSampleRate, value);
    mHSFilter.setParameter(LV_SVFilter::ParameterId::kSampleRate, value);
    mHPFilter.setParameter(LV_SVFilter::ParameterId::kSampleRate, value);
    mLPFilter.setParameter(LV_SVFilter::ParameterId::kSampleRate, value);
}

float MarauderAudioProcessor::proportionalShelfFilterQ(float gain, bool lowShelf)
{
    if (lowShelf) {
        
        return powf(10.0f, gain / 55.0f) - 0.95f;
        
    } else {
        
        return powf(10.0f, gain / 65.0f) - 0.95f;
    }
}

float MarauderAudioProcessor::proportionalPeakFilterQ(float gain)
{
    if (gain >= 0.0f) {
        
        return powf(10.0f, gain / 65.0f) - 0.95f;
        
    } else {
        
        return powf(10.0f, gain / 30.0f) - 0.29f;
    }
}
