/*
  ==============================================================================

    StatusBar.h
    Created: 1 Sep 2022 12:34:07am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "gui/interfaces/stoej_resizeable_component.h"
#include "gui/components/stoej_dbg_box.h"
#include "gui/components/stoej_menu_button.h"
#include "gui/components/stoej_preset_text_field.h"
#include "../PluginAssets.h"
#include "stoej_core.h"

//==============================================================================
/*
*/
class StatusBar  : public juce::Component, public stoej::IResizableComponent
{
public:
    juce::Colour stroke_color = juce::Colour(0, 0, 0);
    juce::Colour fill_color = juce::Colour(255, 255, 255);

    StatusBar();

    void paint (juce::Graphics&) override;
    void resized() override;

    std::variant<int, stoej::DynamicSize> getHeight() override;
    std::variant<int, stoej::DynamicSize> getWidth() override;
    void setDP(double dp) override;

private:
    
    const std::unique_ptr<juce::Drawable> sun_ico_ = STOEJ_DRAWABLE_IMG(BinaryData::sundimlight_svg);
	const std::unique_ptr<juce::Drawable> book_ico_ = STOEJ_DRAWABLE_IMG(BinaryData::bookopenlight_svg);
	const std::unique_ptr<juce::Drawable> gauge_ico_ = STOEJ_DRAWABLE_IMG(BinaryData::gaugelight_svg);
	const std::unique_ptr<juce::Drawable> shuffle_ico_ = STOEJ_DRAWABLE_IMG(BinaryData::shuffleangularlight_svg);
    const std::unique_ptr<juce::Drawable> file_plus_ico_ = STOEJ_DRAWABLE_IMG(BinaryData::filepluslight_svg);
    const std::unique_ptr<juce::Drawable> info_ico_ = STOEJ_DRAWABLE_IMG(BinaryData::infolight_svg);
	
    double dp_ = 1.0;
    //stoej::PresetTextField preset_text_field_;
    stoej::MenuButton light_dark_toggle_;
    stoej::MenuButton help_btn_;
    stoej::MenuButton oversample_btn_;
    stoej::MenuButton randomize_btn_;
    stoej::MenuButton init_btn_;
    stoej::DbgBox tooltip_box_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatusBar)
};
