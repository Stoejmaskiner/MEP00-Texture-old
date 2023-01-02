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
#include "Components/StatusBar.h"
#include "Components/MainView.h"

//==============================================================================
/**
*/
class MEP00TextureAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MEP00TextureAudioProcessorEditor (MEP00TextureAudioProcessor& p, juce::AudioProcessorValueTreeState& apvts);
    ~MEP00TextureAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    // width and height are the minimum sizes, which should be driectly based on the
    // Figma design specification.
    //
    // Figma design spec is not based on real pixel sizes, but rather on scalable units
    // of size (pd), so when setting 1pd = 1px, you get the following sizes, which then
    // are multiplied by a scaling factor to achieve the desired size of the UI.
    //
    // Why are the scaled units set to a smaller size than what is normally wanted? Simply
    // put, they are kept small for ease of design. The design language is based around
    // a grid of 12 pd in size, because it is highly composite and easy to work with.
    static constexpr int k_width_ = 420;
    static constexpr int k_height_ = 240;

    // optimal initial scaling factor as tested on a 1080p display
    static constexpr double k_init_scale_ = 2.3;

    static constexpr double k_padding_ = 3;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MEP00TextureAudioProcessor& audioProcessor;
    TitleBar title_bar_;
    Ribbon ribbon_;
    MainView main_view_;
    StatusBar status_bar_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MEP00TextureAudioProcessorEditor)
};
