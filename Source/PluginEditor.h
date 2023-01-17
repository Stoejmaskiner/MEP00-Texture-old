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
#include "gui/interfaces/stoej_resizeable_component.h"
#include "gui/components/stoej_box.h"
#include "gui/components/stoej_dbg_box.h"
#include "gui/components/stoej_button.h"
#include "gui/components/stoej_component.h"
#include "gui/components/stoej_Slider.h"
#include "gui/components/stoej_Value.h"
#include "gui/components/stoej_xy.h"
#include "gui/components/stoej_Ticker.h"

//==============================================================================
/**
*/
class MEP00TextureAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Button::Listener
{
public:
    MEP00TextureAudioProcessorEditor (MEP00TextureAudioProcessor& p, juce::AudioProcessorValueTreeState& apvts);
    ~MEP00TextureAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    //void buttonClicked(juce::Button* b) override;



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
    //StatusBar status_bar_;


    //stoej::PresetTextField preset_text_field_;
    stoej::StoejButton light_dark_toggle_;
    stoej::StoejButton help_btn_;
    stoej::StoejButton oversample_btn_;
    stoej::StoejButton randomize_btn_;
    stoej::StoejButton init_btn_;
    stoej::Ticker tooltip_box_;

    static constexpr double k_padding_2 = 6.0;

    stoej::Box bounding_box_;
    //stoej::DbgBox main_widget_;
    MainGraphic widget_view_;
    //stoej::XY widget_view_;
    stoej::StoejButton grit_btn_;
    stoej::Value density_val_;
    stoej::Value mix_val_;
    //stoej::DbgBox spacer_;
    stoej::StoejSlider hp_fader_;
    stoej::StoejSlider lp_fader_;
    stoej::StoejSlider width_fader_;
    stoej::StoejSlider level_fader_;

    // TODO: components should manage attachment themselves, passing APVTS and stoej::FloatParameter
    using SliderAttach = juce::AudioProcessorValueTreeState::SliderAttachment;
    using UniSliderAttach = std::unique_ptr<SliderAttach>;
    using ButtonAttach = juce::AudioProcessorValueTreeState::ButtonAttachment;
    using UniButtonAttach = std::unique_ptr<ButtonAttach>;
    UniSliderAttach mix_val_attachment_;
    UniSliderAttach density_val_attachment_;
    UniSliderAttach hp_fader_attachment_;
    UniSliderAttach lp_fader_attachment_;
    UniSliderAttach width_fader_attachment_;
    UniSliderAttach level_fader_attachment_;
    UniButtonAttach grit_btn_attachment_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MEP00TextureAudioProcessorEditor)
};
