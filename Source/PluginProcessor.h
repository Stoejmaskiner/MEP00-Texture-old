/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../shared-code/stoej_juce_utils.h"
#include "../shared-code/stoej_mfx.h"
#include "../shared-code/stoej_filters.h"

//==============================================================================
/**
*/
class MEP00TextureAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    MEP00TextureAudioProcessor();
    ~MEP00TextureAudioProcessor() override = default;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void reset() override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;

private: 
    juce::AudioProcessorValueTreeState::ParameterLayout get_parameter_layout_();

    //==============================================================================
    using Gain = juce::dsp::Gain<float>;
    using DryWet = juce::dsp::DryWetMixer<float>;
    using Filter = juce::dsp::StateVariableTPTFilter<float>;

    // meta
    size_t max_size;
    float sample_rate;

    // processors
    stoej::RingModNoiseA rm_noise_a_;
    stoej::RingModNoiseB rm_noise_b_;
    Filter noise_hp_;
    Filter noise_lp_;
    DryWet mixer_;
    Gain post_gain_;

    // param value references
    std::atomic<float>* mode_raw_ptr_;
    std::atomic<float>* width_raw_ptr_;
    std::atomic<float>* mix_raw_ptr_;
    std::atomic<float>* filter_lp_cut_raw_ptr_;
    std::atomic<float>* filter_hp_cut_raw_ptr_;
    std::atomic<float>* post_gain_raw_ptr_;

    // support buffers
    juce::AudioBuffer<float> dry_buffer_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MEP00TextureAudioProcessor)
};
