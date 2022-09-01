/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/Ribbon.h"
#include "Components/TitleBar.h"
#include "utils/stoej_graphics_utils.h"
#include "gui/components/stoej_box.h"

//==============================================================================
/**
*/
class MEP00TextureAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MEP00TextureAudioProcessorEditor (MEP00TextureAudioProcessor&);
    ~MEP00TextureAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    static constexpr int k_width = 414;
    static constexpr int k_height = 277;
    static constexpr double k_init_scale = 1.5;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MEP00TextureAudioProcessor& audioProcessor;
    TitleBar title_bar_;
    Ribbon ribbon_;
    stoej::Box main_view_;
    stoej::Box status_bar_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MEP00TextureAudioProcessorEditor)
};
