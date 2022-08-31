/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MEP00TextureAudioProcessor::MEP00TextureAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    this->sample_rate = 0.0f;
    this->max_size = 0;
}

MEP00TextureAudioProcessor::~MEP00TextureAudioProcessor()
{
}

//==============================================================================
const juce::String MEP00TextureAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MEP00TextureAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MEP00TextureAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MEP00TextureAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MEP00TextureAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MEP00TextureAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MEP00TextureAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MEP00TextureAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MEP00TextureAudioProcessor::getProgramName (int index)
{
    return {};
}

void MEP00TextureAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MEP00TextureAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    this->sample_rate = sampleRate;
    this->max_size = samplesPerBlock;
    auto spec = juce::dsp::ProcessSpec();
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumInputChannels();
    this->white_noise_.prepare(spec);
    this->multiplicative_noise_.prepare(spec);
    
    /*
    this->rm_noise_a_.prepare(spec);
    this->rm_noise_b_.prepare(spec);
}

void MEP00TextureAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MEP00TextureAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MEP00TextureAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    const auto totalNumInputChannels  = getTotalNumInputChannels();
    const auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    /*
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    */

    const float width = *this->apvts.getRawParameterValue(Parameters::noise_width.id);
    const float density = *this->apvts.getRawParameterValue(Parameters::noise_density.id);
    const float mix = *this->apvts.getRawParameterValue(Parameters::noise_mix.id);
    const float filter_lp_cut = *this->apvts.getRawParameterValue(Parameters::filter_lp_cutoff.id);
    const float filter_hp_cut = *this->apvts.getRawParameterValue(Parameters::filter_hp_cutoff.id);
    const float out_level = *this->apvts.getRawParameterValue(Parameters::output_level.id);
    const bool  grit_enable = *this->apvts.getRawParameterValue(Parameters::output_level.id);
    auto block = juce::dsp::AudioBlock<float>(buffer);
    const auto context = juce::dsp::ProcessContextReplacing<float>(block);
    this->multiplicative_noise_.setNoiseWidth(width);
    this->multiplicative_noise_.setNoiseDensity(density);
    this->multiplicative_noise_.setNoiseMix(mix);
    this->multiplicative_noise_.setFilterLPCutoff(filter_lp_cut);
    this->multiplicative_noise_.setFilterHPCutoff(filter_hp_cut);
    this->multiplicative_noise_.setOutLevel(out_level);
    this->multiplicative_noise_.setGritEnable(grit_enable);
    this->multiplicative_noise_.process(context);

    //this->white_noise_.process(stoej::buff_to_context(buffer));



    //this->rm_noise_a_.process(stoej::buff_to_context(buffer)); 
    //this->rm_noise_b_.process(stoej::buff_to_context(buffer));
}

//==============================================================================
bool MEP00TextureAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MEP00TextureAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
    //return new MEP00TextureAudioProcessorEditor (*this);
}

//==============================================================================
void MEP00TextureAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MEP00TextureAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MEP00TextureAudioProcessor();
}
