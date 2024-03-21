/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MarauderAudioProcessor::MarauderAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState (*this, nullptr, "PARAMETER", createParameterLayout()),
oversamplingProcessor (2, 2, juce::dsp::Oversampling<float>::FilterType::filterHalfBandPolyphaseIIR, true, false)

#endif
{
    treeState.addParameterListener (driveSliderId, this);
    treeState.addParameterListener (trimSliderId, this);
    treeState.addParameterListener (phaseId, this);
    treeState.addParameterListener (jitterId, this);
    treeState.addParameterListener (resampleId, this);
    treeState.addParameterListener (bitDepthId, this);
    treeState.addParameterListener (noiseId, this);
    treeState.addParameterListener (mixId, this);
    treeState.addParameterListener (highCutId, this);
}

MarauderAudioProcessor::~MarauderAudioProcessor()
{
    treeState.removeParameterListener (driveSliderId, this);
    treeState.removeParameterListener (trimSliderId, this);
    treeState.removeParameterListener (phaseId, this);
    treeState.removeParameterListener (jitterId, this);
    treeState.removeParameterListener (resampleId, this);
    treeState.removeParameterListener (bitDepthId, this);
    treeState.removeParameterListener (noiseId, this);
    treeState.removeParameterListener (mixId, this);
    treeState.removeParameterListener (highCutId, this);
}

//==============================================================================
const juce::String MarauderAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MarauderAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MarauderAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MarauderAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MarauderAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MarauderAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MarauderAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MarauderAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MarauderAudioProcessor::getProgramName (int index)
{
    return {};
}

void MarauderAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    
}

//==============================================================================
void MarauderAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize spec for dsp modules
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate * oversamplingProcessor.getOversamplingFactor();
    spec.numChannels = getTotalNumOutputChannels();
    
    // Set the sample rate and use it for dsp modules
    // We need both samplerates to switch between oversampling states
    lastSampleRate = spec.sampleRate;
    projectSampleRate = sampleRate;
    
    // Initialize global variables to corresponding params to make sure they load properly
    setPhase(*treeState.getRawParameterValue(phaseId));

    // Initialize trim gain
    lastTrimGain = pow(10, *treeState.getRawParameterValue(trimSliderId) / 20);
    currentTrimGain = pow(10, *treeState.getRawParameterValue(trimSliderId) / 20);
    
    // Bit Crusher
    bitCrusherModule.prepare(spec);
    bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kPreamp, *treeState.getRawParameterValue(driveSliderId));
    bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kResampledRate, *treeState.getRawParameterValue(resampleId));
    bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kBitDepth, *treeState.getRawParameterValue(bitDepthId));
    bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kNoiseGain, *treeState.getRawParameterValue(noiseId));
    bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kMix, *treeState.getRawParameterValue(mixId));
    bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kJitter, *treeState.getRawParameterValue(jitterId));
    
    // Filter
    hpFilter.reset();
    hpFilter.prepare(spec);
    hpFilter.setParameter(LV_SVFilter::ParameterId::kType, LV_SVFilter::kHighPass);
    hpFilter.setParameter(LV_SVFilter::ParameterId::kCutoff, *treeState.getRawParameterValue(highCutId));
    
    // Oversampling
    oversamplingProcessor.initProcessing(spec.maximumBlockSize);
    oversamplingProcessor.reset();
    
    currentDrive = *treeState.getRawParameterValue(driveSliderId);
}

void MarauderAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MarauderAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MarauderAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Audio block for dsp modules
    juce::dsp::AudioBlock<float> audioBlock {buffer};
    juce::dsp::AudioBlock<float> upSampledBlock;
    
    /*==========================================================================*/
    
    // Oversample up
    hpFilter.setParameter(LV_SVFilter::ParameterId::kSampleRate, lastSampleRate);
    upSampledBlock = oversamplingProcessor.processSamplesUp(audioBlock);
    
    // Filter
    hpFilter.process(upSampledBlock, buffer.getNumChannels());
    
    // Bit Crusher
    bitCrusherModule.render(upSampledBlock, buffer.getNumChannels());
    
    // Sample back down
    oversamplingProcessor.processSamplesDown(audioBlock);
    
    // Trim gain and smoothing
    if (currentTrimGain == lastTrimGain)
    {
        buffer.applyGain(0, buffer.getNumSamples(), currentTrimGain);
    }
    
    else
    {
        buffer.applyGainRamp(0, buffer.getNumSamples(), lastTrimGain, currentTrimGain);
        lastTrimGain = currentTrimGain;
    }
    
    // Phase
    buffer.applyGain(currentPhase);
}

juce::AudioProcessorValueTreeState::ParameterLayout MarauderAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // Make sure to update the number of reservations after adding params
    params.reserve(9);
    
    auto pDrive = std::make_unique<juce::AudioParameterFloat>(driveSliderId, driveSliderName, 0.0f, 12.0f, 0.0f);
    auto pTrim = std::make_unique<juce::AudioParameterFloat>(trimSliderId, trimSliderName, -24.0f, 24.0f, 0.0f);
    
    auto pFilter = std::make_unique<juce::AudioParameterInt>(highCutId, highCutName, 40, 500, 50);
    auto pResample = std::make_unique<juce::AudioParameterInt>(resampleId, resampleName, 100, 44100, 44100);
    auto pBitDepth = std::make_unique<juce::AudioParameterInt>(bitDepthId, bitDepthName, 6, 16, 16);
    auto pNoise = std::make_unique<juce::AudioParameterFloat>(noiseId, noiseName, 0.0f, 16.0f, 0.0f);
    auto pMix = std::make_unique<juce::AudioParameterInt>(mixId, mixName, 0, 100, 100);
    
    auto pPhase = std::make_unique<juce::AudioParameterBool>(phaseId, phaseName, false);
    auto pJitter = std::make_unique<juce::AudioParameterBool>(jitterId, jitterName, false);

    params.push_back(std::move(pDrive));
    params.push_back(std::move(pTrim));
    
    params.push_back(std::move(pFilter));
    params.push_back(std::move(pResample));
    params.push_back(std::move(pBitDepth));
    params.push_back(std::move(pNoise));
    params.push_back(std::move(pMix));
    
    params.push_back(std::move(pPhase));
    params.push_back(std::move(pJitter));

    return { params.begin(), params.end() };
}

void MarauderAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue){
    
    // Update params here
    if (parameterID == driveSliderId)
    {
        bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kPreamp, newValue);
        currentDrive = newValue;
    }

    else if (parameterID == trimSliderId) {
        
        currentTrimGain = pow(10, newValue / 20);
        
    } else  if (parameterID == phaseId) {
        
        setPhase(newValue);
        
    } else  if (parameterID == resampleId) {
        
        bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kResampledRate, newValue);
        
    } else  if (parameterID == bitDepthId) {
        
        bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kBitDepth, newValue);
        
    } else  if (parameterID == noiseId) {
        
        bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kNoiseGain, newValue);
        
    } else  if (parameterID == mixId) {
        
        bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kMix, newValue);
        
    } else  if (parameterID == highCutId) {
        
        hpFilter.setParameter(LV_SVFilter::ParameterId::kCutoff, newValue);
        
    } else if (parameterID == jitterId){
        
        bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kJitter, newValue);
    }
}
//==============================================================================
bool MarauderAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MarauderAudioProcessor::createEditor()
{
    return new MarauderAudioProcessorEditor (*this);
}

//==============================================================================
void MarauderAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Save params
    treeState.state.appendChild(variableTree, nullptr);
    juce::MemoryOutputStream stream(destData, false);
    treeState.state.writeToStream (stream);
}

void MarauderAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Recall params
    auto tree = juce::ValueTree::readFromData (data, size_t(sizeInBytes));
    variableTree = tree.getChildWithName("Variables");
    
    if (tree.isValid())
    {
        treeState.state = tree;
    }
    
    windowWidth = variableTree.getProperty("width");
    windowHeight = variableTree.getProperty("height");
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MarauderAudioProcessor();
}

void MarauderAudioProcessor::setPhase(bool phase)
{
    if (phase){
        
        currentPhase = -1;
        
    } else {
        
        currentPhase = 1;
    }
}

void MarauderAudioProcessor::setAllSampleRates(float value)
{
    bitCrusherModule.setParameter(LV_BitCrusher::ParameterId::kSampleRate, value);
}
