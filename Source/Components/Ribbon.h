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
    void paintOverChildren(juce::Graphics& g) override;
    void resized() override;

    std::variant<int, stoej::DynamicSize> getHeight() override;
    std::variant<int, stoej::DynamicSize> getWidth() override;
    void setDP(double dp) override;

private:
    const std::unique_ptr<juce::Drawable> list_ico_ = 
        juce::Drawable::createFromImageData(BinaryData::listlight_svg, BinaryData::listlight_svgSize);
    const std::unique_ptr<juce::Drawable> folder_ico_ = 
        juce::Drawable::createFromImageData(BinaryData::folderopenlight_svg, BinaryData::folderopenlight_svgSize);
    const std::unique_ptr<juce::Drawable> left_ico_ =
        juce::Drawable::createFromImageData(BinaryData::caretleftlight_svg, BinaryData::caretleftlight_svgSize);
    const std::unique_ptr<juce::Drawable> right_ico_ =
        juce::Drawable::createFromImageData(BinaryData::caretrightlight_svg, BinaryData::caretrightlight_svgSize);
    const std::unique_ptr<juce::Drawable> floppy_ico_ =
        juce::Drawable::createFromImageData(BinaryData::floppydisklight_svg, BinaryData::floppydisklight_svgSize);

    double dp_ = 1.0;
    //stoej::Box bounding_box_;
    stoej::DbgBox dbg_box_;
    stoej::MenuButton burger_menu_btn_;
    stoej::MenuButton browse_presets_btn_;
    stoej::MenuButton previous_preset_btn_;
    stoej::MenuButton next_preset_btn_;
    stoej::MenuButton save_preset_btn_;
    stoej::DbgBox light_dark_theme_tgl_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ribbon)
};
