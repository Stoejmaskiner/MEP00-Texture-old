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
#include "../PluginParameters.h"

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
    stoej::DbgBox widget_view_;
    stoej::StoejButton grit_btn_;
    stoej::DbgBox density_val_;
    stoej::DbgBox mix_val_;
    stoej::DbgBox spacer_;
    stoej::DbgBox hp_fader_;
    stoej::StoejSlider lp_fader_;
    stoej::DbgBox width_fader_;
    stoej::DbgBox level_fader_;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lp_fader_attachment_;
    //stoej::Component test_;
    //stoej::Component test2_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainView)
};