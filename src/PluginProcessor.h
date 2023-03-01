#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>
#include <stoej_dsp/stoej_dsp.h>
#include <stoej_gui/stoej_gui.h>

#include "PluginParameters.h"

namespace fp000 {
    class PluginProcessor : public juce::AudioProcessor {
    public:
        PluginProcessor();
        ~PluginProcessor() override {}

    // the apvts is used to store parameters and plugin state
        stoej::APVTS apvts{
            *this, nullptr, FP000_PRODUCT_CODE, []()
            {
                // TODO: this should be a method, defined in cpp file

                juce::AudioProcessorValueTreeState::ParameterLayout layout;

                // public parameters
                for (auto& [_, info] : fp000::bool_params)
                    layout.add(stoej::create_unique_param_bool(info));
                for (auto& [_, info] : fp000::float_params)
                    layout.add(stoej::create_unique_param_float(info));

                return layout;
            }()
        };

        stoej::ThemeManager theme_manager_;

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

    private:
        //==============================================================================
        using Gain = juce::dsp::Gain<float>;
        using DryWet = juce::dsp::DryWetMixer<float>;
        using Filter = juce::dsp::StateVariableFilter::Filter<float>;
        
        size_t max_size;
        float sample_rate;

        //stoej::WhiteNoise<float> white_noise_;
        stoej::MultiplicativeNoise<float> multiplicative_noise_;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
    };
}