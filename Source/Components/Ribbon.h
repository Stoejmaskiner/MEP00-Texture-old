/*
  ==============================================================================

    Ribbon.h
    Created: 1 Sep 2022 12:33:19am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "gui/components/stoej_box.h"
#include "gui/components/stoej_dbg_box.h"
#include "gui/components/stoej_menu_button.h"
#include "gui/components/stoej_preset_text_field.h"
#include "binary_data/stoej_BinaryData.h"
#include "binary_data/stoej_Fonts.h"
#include "stoej_core.h"
#include "../PluginAssets.h"

//==============================================================================
/*
*/
class Ribbon  : public juce::Component, public stoej::IResizableComponent
{
	
public:
    juce::Colour stroke_color = juce::Colour(  0,   0,   0);
    juce::Colour fill_color   = juce::Colour(255, 255, 255);

    Ribbon();
    ~Ribbon() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

    std::variant<int, stoej::DynamicSize> getHeight() override;
    std::variant<int, stoej::DynamicSize> getWidth() override;
    void setDP(double dp) override;

private:
    const std::unique_ptr<juce::Drawable> list_ico_ = STOEJ_DRAWABLE_IMG(stoej_BinaryData::listlight_svg);
    const std::unique_ptr<juce::Drawable> folder_ico_ = STOEJ_DRAWABLE_IMG(stoej_BinaryData::folderopenlight_svg);
    const std::unique_ptr<juce::Drawable> left_ico_ = STOEJ_DRAWABLE_IMG(stoej_BinaryData::caretleftlight_svg);
    const std::unique_ptr<juce::Drawable> right_ico_ = STOEJ_DRAWABLE_IMG(stoej_BinaryData::caretrightlight_svg);
    const std::unique_ptr<juce::Drawable> floppy_ico_ = STOEJ_DRAWABLE_IMG(stoej_BinaryData::floppydisklight_svg);
    const std::unique_ptr<juce::Drawable> person_ = STOEJ_DRAWABLE_IMG(stoej_BinaryData::userlight_svg);

    double dp_ = 1.0;
    //stoej::Box bounding_box_;
    stoej::PresetTextField preset_text_field_;
    stoej::MenuButton burger_menu_btn_;
    stoej::MenuButton browse_presets_btn_;
    stoej::MenuButton previous_preset_btn_;
    stoej::MenuButton next_preset_btn_;
    stoej::MenuButton save_preset_btn_;
    stoej::DbgBox light_dark_theme_tgl_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ribbon)
};
