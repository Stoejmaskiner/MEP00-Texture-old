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
#include "binary_data/stoej_BinaryData.h"
#include "../PluginAssets.h"
#include "stoej_core.h"
#include "gui/components/stoej_Ticker.h"

//==============================================================================
/*
*/
class StatusBar  : public juce::Component, public stoej::IResizableComponent
{
public:
    juce::Colour stroke_color = juce::Colour(0, 0, 0);
    juce::Colour fill_color = juce::Colour(255, 255, 255);

    StatusBar(stoej::APVTS& apvts);

    void paint (juce::Graphics&) override;
    void resized() override;

    std::variant<int, stoej::DynamicSize> getHeight() override;
    std::variant<int, stoej::DynamicSize> getWidth() override;
    void setDP(double dp) override;

    stoej::Ticker* getTooltipBox() { return &this->tooltip_box_; }

private:
    using DrawPtr = std::unique_ptr<juce::Drawable>;
    const DrawPtr sun_ico_ = STOEJ_DRAWABLE_IMG(stoej_BinaryData::sundimlight_svg);
	const DrawPtr book_ico_ = STOEJ_DRAWABLE_IMG(stoej_BinaryData::bookopenlight_svg);
	const DrawPtr gauge_ico_ = STOEJ_DRAWABLE_IMG(stoej_BinaryData::gaugelight_svg);
	const DrawPtr shuffle_ico_ = STOEJ_DRAWABLE_IMG(stoej_BinaryData::shuffleangularlight_svg);
    const DrawPtr file_plus_ico_ = STOEJ_DRAWABLE_IMG(stoej_BinaryData::filepluslight_svg);
    const DrawPtr info_ico_ = STOEJ_DRAWABLE_IMG(stoej_BinaryData::infolight_svg);
	
    double dp_ = 1.0;
    //stoej::PresetTextField preset_text_field_;
    juce::ToggleButton light_dark_toggle_;
    stoej::MenuButton help_btn_;
    //stoej::MenuButton oversample_btn_;
    stoej::MenuButton randomize_btn_;
    stoej::MenuButton init_btn_;
    stoej::Ticker tooltip_box_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatusBar)
};
