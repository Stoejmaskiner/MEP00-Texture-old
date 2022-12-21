/*
  ==============================================================================

    MainView.h
    Created: 1 Sep 2022 12:33:37am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "gui/interfaces/stoej_resizeable_component.h"
#include "gui/components/stoej_box.h"
#include "gui/components/stoej_dbg_box.h"
#include "gui/components/stoej_button.h"
#include "gui/components/stoej_component.h"
#include "gui/components/stoej_Slider.h"
#include "gui/components/stoej_Value.h"
#include "../PluginParameters.h"
#include "MainGraphic.h"

//==============================================================================
/*
*/
class MainView  : public juce::Component, public stoej::IResizableComponent
{
public:
    MainView(juce::AudioProcessorValueTreeState& apvts);
    ~MainView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setDP(double dp) override;

    std::variant<int, stoej::DynamicSize> getHeight() override;
    std::variant<int, stoej::DynamicSize> getWidth() override;

private:
    
    static constexpr int k_padding_ = 6;
    double dp_;
    stoej::Box bounding_box_;
    //stoej::DbgBox main_widget_;
    MainGraphic widget_view_;
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
    //stoej::Component test_;
    //stoej::Component test2_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainView)
};