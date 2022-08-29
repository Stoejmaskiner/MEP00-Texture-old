/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"

#include <cassert>

#include "PluginEditor.h"

//==============================================================================
MEP00TextureAudioProcessor::MEP00TextureAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), apvts(
        *this,
        nullptr,
        "Parameters",
        this->get_parameter_layout_()
    )
#else
    : apvts(
        *this,
        nullptr,
        "Parameters",
        this->get_parameter_layout_()
    )
#endif
	
{
	this->sample_rate = 0.0f;
	this->max_size = 0;
	this->noise_lp_.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
	this->noise_hp_.setType(juce::dsp::StateVariableTPTFilterType::highpass);
    this->mixer_.setWetLatency(0.0f);
    this->mixer_.setMixingRule(juce::dsp::DryWetMixingRule::linear);

    this->mode_raw_ptr_ = this->apvts.getRawParameterValue("MODE");
    this->mix_raw_ptr_ = this->apvts.getRawParameterValue("MIX");
    this->width_raw_ptr_ = this->apvts.getRawParameterValue("WIDTH");
    this->filter_lp_cut_raw_ptr_ = this->apvts.getRawParameterValue("FILTER_LP_CUTOFF");
    this->filter_hp_cut_raw_ptr_ = this->apvts.getRawParameterValue("FILTER_HP_CUTOFF");
    this->post_gain_raw_ptr_ = this->apvts.getRawParameterValue("POST_GAIN");

    this->dry_buffer_ = juce::AudioBuffer<float>();
}


//==============================================================================
const juce::String MEP00TextureAudioProcessor::getName() const { return JucePlugin_Name; }
bool MEP00TextureAudioProcessor::acceptsMidi() const { return false; }
bool MEP00TextureAudioProcessor::producesMidi() const { return false; }
bool MEP00TextureAudioProcessor::isMidiEffect() const { return false; }
double MEP00TextureAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int MEP00TextureAudioProcessor::getNumPrograms() { return 1; }  // should always be at least 1 even if irrelevant
int MEP00TextureAudioProcessor::getCurrentProgram() { return 0; }
void MEP00TextureAudioProcessor::setCurrentProgram (int index) {}
const juce::String MEP00TextureAudioProcessor::getProgramName (int index) { return {}; }
void MEP00TextureAudioProcessor::changeProgramName (int index, const juce::String& newName) {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MEP00TextureAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
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


//==============================================================================
void MEP00TextureAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    this->sample_rate = sampleRate;
    this->max_size = samplesPerBlock;
    size_t num_channels = this->getTotalNumInputChannels();
    jassert(num_channels > 0);
    jassert(samplesPerBlock > 0);
    jassert(sampleRate > 0);
    auto spec = juce::dsp::ProcessSpec();
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = num_channels;
    this->rm_noise_a_.prepare(spec);
    this->rm_noise_b_.prepare(spec);

    this->dry_buffer_.setSize(num_channels, this->max_size);
    this->noise_lp_.prepare(spec);
    this->mixer_.prepare(spec);

    /*
    this->noise_hp_.prepare(spec);
    this->mixer_.prepare(spec);
    this->post_gain_.prepare(spec);
    */
}

void MEP00TextureAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void MEP00TextureAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{

    // sanitize
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    if (totalNumInputChannels != totalNumOutputChannels) return;
    if (buffer.getNumSamples() > this->max_size) return;
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // update params
    const bool gritty = *this->mode_raw_ptr_ > 0.5f;
    const float width = *this->width_raw_ptr_;
    this->rm_noise_a_.noise_width = width;
    this->rm_noise_b_.noise_width = width;

    const float mix = *this->mix_raw_ptr_;
    this->mixer_.setWetMixProportion(mix);

    const float filter_lp_cutoff = *this->filter_lp_cut_raw_ptr_;
    /*
    float mix = apvts.getParameterAsValue("MIX").getValue();
    float width = apvts.getParameterAsValue("WIDTH").getValue();
    float filter_lp_cutoff = apvts.getParameterAsValue("FILTER_LP_CUTOFF").getValue();
    float filter_hp_cutoff = apvts.getParameterAsValue("FILTER_HP_CUTOFF").getValue();
    float post_gain = apvts.getParameterAsValue("POST_GAIN").getValue();
    this->rm_noise_a_.noise_width = width;
    this->rm_noise_b_.noise_width = width;
    this->noise_lp_.setCutoffFrequency(filter_lp_cutoff);
    this->noise_hp_.setCutoffFrequency(filter_hp_cutoff);
    this->mixer_.setWetMixProportion(mix);
    this->post_gain_.setGainDecibels(post_gain);
    */

    // process

    this->mixer_.setWetLatency(0);
    this->mixer_.pushDrySamples(stoej::buff_to_block(buffer));

    if (gritty)
    {
        this->rm_noise_b_.process(stoej::buff_to_context(buffer));
    } else
    {
        this->rm_noise_a_.process(stoej::buff_to_context(buffer));
    }

    this->noise_lp_.process(stoej::buff_to_context(buffer));
    //this->noise_hp_.process(context);
    this->mixer_.mixWetSamples(stoej::buff_to_block(buffer));
    //this->post_gain_.process(context);
}

void MEP00TextureAudioProcessor::reset()
{
    /*
    this->noise_lp_.reset();
    this->noise_hp_.reset();
    this->rm_noise_a_.reset();
    this->rm_noise_b_.reset();
    this->mixer_.reset();
    this->post_gain_.reset();
    */
}

//==============================================================================
bool MEP00TextureAudioProcessor::hasEditor() const { return true; }

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

juce::AudioProcessorValueTreeState::ParameterLayout
MEP00TextureAudioProcessor::get_parameter_layout_()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(
        stoej::UniqueParamBool("MODE", "simple / gritty", true),
        stoej::UniqueParamFloat(
            "MIX", "dry / wet",
            juce::NormalisableRange<float>(0.0f, 1.0f),
            0.5f),
        stoej::UniqueParamFloat(
            "WIDTH", "noise width",
            juce::NormalisableRange<float>(0.0f, 1.0f),
            0.5f),
        stoej::UniqueParamFloat(
            "FILTER_LP_CUTOFF", "LP cutoff",
            juce::NormalisableRange<float>(20.0f, 18000.0f, 0.0f, 0.3f),
            12000.0f),
        stoej::UniqueParamFloat(
            "FILTER_HP_CUTOFF", "HP cutoff",
            juce::NormalisableRange<float>(5.0f, 16000.0f, 0.3f),
            60.0f),
        stoej::UniqueParamFloat(
            "POST_GAIN", "post gain",
            juce::NormalisableRange<float>(0.0f, 2.0f, 0.0f, 0.5f),
            1.0f
        )

    );
    return layout;
}