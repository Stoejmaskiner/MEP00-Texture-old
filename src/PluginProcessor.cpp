#pragma once
#include <stoej_core/stoej_core.h>
#include <stoej_gui/stoej_gui.h>

#include "PluginProcessor.h"
#include "PluginEditor.h"

// TODO: consteval this
fp000::PluginProcessor::PluginProcessor() 
    : 
#ifndef JucePlugin_PreferredChannelConfigurations  
    AudioProcessor(
        BusesProperties()
        #if ! JucePlugin_IsMidiEffect
            #if ! JucePlugin_IsSynth
            .withInput("Input", juce::AudioChannelSet::stereo(), true)
            #endif
            .withOutput("Output", juce::AudioChannelSet::stereo(), true)
        #endif
    ),
#endif
    theme_manager_()
{
    this->sample_rate = 0.0f;
    this->max_size = 0;
}


// ===== JUCE boilerplate (TODO: macro?) ======================================

const juce::String fp000::PluginProcessor::getName() const {
    return JucePlugin_Name;
}

bool fp000::PluginProcessor::acceptsMidi() const {
    return static_cast<bool>(JucePlugin_WantsMidiInput);
}

bool fp000::PluginProcessor::producesMidi() const {
    return static_cast<bool>(JucePlugin_ProducesMidiOutput);
}

bool fp000::PluginProcessor::isMidiEffect() const {
    return static_cast<bool>(JucePlugin_IsMidiEffect);
}

double fp000::PluginProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int fp000::PluginProcessor::getNumPrograms() {
    // NB: some hosts don't cope very well if you tell them there are 0
    // programs, so this should be at least 1, even if you're not really 
    // implementing programs.
    return 1;
}

int fp000::PluginProcessor::getCurrentProgram() {
    return 0;
}

void fp000::PluginProcessor::setCurrentProgram(int) {}

const juce::String fp000::PluginProcessor::getProgramName(int) {
    return {};
}

void fp000::PluginProcessor::changeProgramName(int, const juce::String&) {}


// ===== actually important stuff =============================================

void fp000::PluginProcessor::prepareToPlay(
    double sample_rate, 
    int max_size)
{
    this->sample_rate = sample_rate;
    this->max_size = max_size;
    auto spec = juce::dsp::ProcessSpec();
    spec.maximumBlockSize = max_size;
    spec.sampleRate = sample_rate;
    spec.numChannels = this->getTotalNumInputChannels();
    this->multiplicative_noise_.prepare(spec);
}


void fp000::PluginProcessor::releaseResources() {}


#ifndef JucePlugin_PreferredChannelConfigurations
bool fp000::PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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


void fp000::PluginProcessor::processBlock(
    juce::AudioBuffer<float>& buffer, 
    juce::MidiBuffer& midi_messages) 
{
    // magically improve float arithmetic performance
    juce::ScopedNoDenormals no_denormals;
    const auto total_num_input_channels = getTotalNumInputChannels();
    const auto total_num_output_channels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = total_num_input_channels; i < total_num_output_channels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    
    
    // FIXME: this is ass
    const float width = *this->apvts.getRawParameterValue(
        fp000::float_params.at(fp000::FloatParamNames::noise_width).id);
    const float density = *this->apvts.getRawParameterValue(
        fp000::float_params.at(fp000::FloatParamNames::noise_density).id);
    const float mix = *this->apvts.getRawParameterValue(
        fp000::float_params.at(fp000::FloatParamNames::noise_mix).id);
    const float filter_lp_cut = *this->apvts.getRawParameterValue(
        fp000::float_params.at(fp000::FloatParamNames::filter_lp_cutoff).id);
    const float filter_hp_cut = *this->apvts.getRawParameterValue(
        fp000::float_params.at(fp000::FloatParamNames::filter_hp_cutoff).id);
    const float out_level = *this->apvts.getRawParameterValue(
        fp000::float_params.at(fp000::FloatParamNames::output_level).id);
    
    const bool grit_enable = *this->apvts.getRawParameterValue(
        fp000::bool_params.at(fp000::BoolParamNames::enable_grit).id);
    
    this->multiplicative_noise_.setNoiseWidth(width);
    this->multiplicative_noise_.setNoiseDensity(density);
    this->multiplicative_noise_.setNoiseMix(mix);
    this->multiplicative_noise_.setFilterLPCutoff(filter_lp_cut);
    this->multiplicative_noise_.setFilterHPCutoff(filter_hp_cut);
    this->multiplicative_noise_.setOutLevel(out_level);
    this->multiplicative_noise_.setGritEnable(grit_enable);
    
    auto block = juce::dsp::AudioBlock<float>(buffer);
    const auto context = juce::dsp::ProcessContextReplacing<float>(block);

    this->multiplicative_noise_.process(context);
}


// ===== editor bootstrap =====================================================
bool fp000::PluginProcessor::hasEditor() const {
    return true;
}

juce::AudioProcessorEditor* fp000::PluginProcessor::createEditor() {
    return new fp000::PluginEditor(*this, this->apvts, this->theme_manager_);
}


// ===== state shenanigans ====================================================

void fp000::PluginProcessor::getStateInformation (juce::MemoryBlock& dest_data) {
    // TODO: probably needs to be rewritten and simplified, also use JSON for
    // gods sake

    STOEJ_DBG(1, "preparing preset from state");
    juce::ValueTree state(FP000_PRODUCT_CODE);
    
    // FIXME: maybe a small amount of stringly typedness is okay...
    // FIXME: stringly typed
    state.setProperty("STOEJ_PRESET_SCHEMA_VERSION", 0, nullptr);
    STOEJ_VT_SET_AUTONAMED_PROPERTY(state, FP000_PRODUCT_CODE);
    STOEJ_VT_SET_AUTONAMED_PROPERTY(state, JUCE_STRINGIFY(JucePlugin_Version));
    STOEJ_VT_SET_AUTONAMED_PROPERTY(state, FP000_PRODUCT_CODE);
    for (auto& [_, info] : fp000::bool_params) {
        // FIXME: stringly typed
        juce::ValueTree param("PARAM");
        param.setProperty("id", info.id, nullptr);
        param.setProperty("value", this->apvts.getRawParameterValue(info.id)->load(), nullptr);
        state.appendChild(param, nullptr);
    }
    for (auto& [_, info] : fp000::float_params) {
        // FIXME: stringly typed
        juce::ValueTree param("PARAM");
        param.setProperty("id", info.id, nullptr);
        float val = this->apvts.getParameter(info.id)->getNormalisableRange().convertTo0to1(this->apvts.getRawParameterValue(info.id)->load());
        param.setProperty("value", val, nullptr);
        state.appendChild(param, nullptr);
    }
    STOEJ_DBG(0, "finished preparing preset. preset:\n:" + state.toXmlString().toStdString());
    STOEJ_DBG(1, "saving preset");
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary(*xml, dest_data);
    STOEJ_DBG(0, "saved preset");
}

void fp000::PluginProcessor::setStateInformation (
    const void* data, 
    int size_in_bytes) 
{
    // TODO: probably needs to be rewritten and simplified, also use JSON for
    // gods sake

    std::unique_ptr<juce::XmlElement> xml_state(getXmlFromBinary(data, size_in_bytes));

    // TODO: graceful error reporting
    if (xml_state.get() == nullptr) {
        STOEJ_DBG(3, "import aborted, could not load XML (was nullptr)");
        jassertfalse;
    }

    auto state = juce::ValueTree::fromXml(*xml_state);
    if (state.getType() != this->apvts.state.getType()) {
        STOEJ_DBG(2, "root type mismatch. expected=<" + this->apvts.state.getType().toString().toStdString() + ">, got=<" + state.getType().toString().toStdString() + ">");
    }

    const juce::String got_product_code = STOEJ_VT_GET_AUTONAMED_PROPERTY_CHECKED(state, PRODUCT_CODE);
    if (got_product_code != FP000_PRODUCT_CODE) {
        STOEJ_DBG(3, "import aborted, attempting to import preset from a different product. expected=<" + std::string(FP000_PRODUCT_CODE) + ">, got=<" + got_product_code.toStdString() + ">");
        jassertfalse;
    }

    // TODO: check schema version
    auto version = JUCE_STRINGIFY(JucePlugin_Version);
    const juce::String got_version = STOEJ_VT_GET_AUTONAMED_PROPERTY_CHECKED(state, version);
    switch (stoej::semVerCompare(got_version), version) {
        case lt:
        case eq:
            break;
        case lt_breaking:
            STOEJ_DBG(1,"importing from an older major version, special handling may be performed. expected=<" + std::string(version) + ">, got=<" + got_version.toStdString() + ">");
            break;
        case gt_breaking:
            STOEJ_DBG(3,"import aborted, trying to import from a newer major version. expected=<" + std::string(version) + ">, got=<" + got_version.toStdString() + ">");
            jassertfalse;
            break;
        case gt:
            STOEJ_DBG(2,"importing from a future minor version");
            jassertfalse;
            break;
        default:
            jassertfalse;
    } 

    // load params
    for (auto& [_, info] : bool_params) {
        auto param = state.getChildWithProperty("id",info.id);
        this->apvts.getParameter(info.id)->setValueNotifyingHost(param.getProperty("value"));        
    }
    for (auto& [_, info] : float_params) {
        auto param = state.getChildWithProperty("id", info.id);
        this->apvts.getParameter(info.id)->setValueNotifyingHost(param.getProperty("value"));        
    }
}


// ===== entrypoint ===========================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new fp000::PluginProcessor();
}