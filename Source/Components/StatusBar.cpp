/*
  ==============================================================================

    StatusBar.cpp
    Created: 1 Sep 2022 12:34:07am
    Author:  Lorenzo

  ==============================================================================
*/


#include "StatusBar.h"

//==============================================================================
StatusBar::StatusBar(stoej::ThemedAPVTS& apvts) :
//preset_text_field_(get_font_archivo_narrow_bold(), get_font_archivo_narrow_light()),
//light_dark_toggle_(this->sun_ico_),
help_btn_(this->book_ico_),
//oversample_btn_(this->gauge_ico_),
randomize_btn_(this->shuffle_ico_),
init_btn_(this->file_plus_ico_),
tooltip_box_(apvts, "tooltip_box")
/*save_preset_btn_(this->floppy_ico_)*/ {
    // setting edge visibility to avoid redrawing adjacent edges
    //this->light_dark_toggle_.setTilePosition(stoej::e_array_left);
    this->help_btn_.setTilePosition(stoej::e_array_horizontal);
    //this->oversample_btn_.setTilePosition(stoej::e_array_horizontal);
    this->randomize_btn_.setTilePosition(stoej::e_array_horizontal);
    this->init_btn_.setTilePosition(stoej::e_array_horizontal);
  //  this->preset_text_field_.setTilePosition(stoej::e_array_horizontal);

    //this->addAndMakeVisible(this->preset_text_field_);
    this->addAndMakeVisible(this->light_dark_toggle_);
    this->addAndMakeVisible(this->help_btn_);
    //this->addAndMakeVisible(this->oversample_btn_);
    this->addAndMakeVisible(this->randomize_btn_);
    this->addAndMakeVisible(this->init_btn_);
    this->addAndMakeVisible(this->tooltip_box_);

    this->light_dark_toggle_.setTooltip("gneurshk");
    this->light_dark_toggle_.addMouseListener(&this->tooltip_box_, false);
}


void StatusBar::paint (juce::Graphics& g)
{

}

void StatusBar::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto r = this->getLocalBounds();
    //this->bounding_box_.setBounds(r);
    //r.reduce(12*this->dp_,12*this->dp_);
    //this->dbg_box_.setBounds(r);

    // left hand buttons
    /*
    this->light_dark_toggle_.setBounds(
        r.removeFromLeft(std::get<int>(this->light_dark_toggle_.getWidth()) * dp_));
    */
    this->light_dark_toggle_.setBounds(r.removeFromLeft(24 * dp_));
    this->help_btn_.setBounds(
        r.removeFromLeft(std::get<int>(this->help_btn_.getWidth()) * dp_));
    //this->oversample_btn_.setBounds(
    //    r.removeFromLeft(std::get<int>(this->oversample_btn_.getWidth()) * dp_));
    this->randomize_btn_.setBounds(
        r.removeFromLeft(std::get<int>(this->randomize_btn_.getWidth()) * dp_));
    this->init_btn_.setBounds(
        r.removeFromLeft(std::get<int>(this->init_btn_.getWidth()) * dp_));

    this->tooltip_box_.setFloatBounds(r);

    // right hand buttons
    //this->tooltip_box_.setBounds(
    //    r.removeFromRight(std::get<int>(this->save_preset_btn_.getWidth()) * dp_));
    //this->save_preset_btn_.setBounds(
    //    r.removeFromRight(std::get<int>(this->save_preset_btn_.getWidth()) * dp_));

    // text box
    //this->preset_text_field_.setBounds(r);
}


std::variant<int, stoej::DynamicSize> StatusBar::getHeight() {
    // TODO(Lorenzo) when shared-code/#1 is implemented, this should automatically
    // determine the height of the ribbon based on the height of the child component array
    //
    // the component array should refuse inconsistent component sizes and return the
    // size of its children when queried.
	
    //return std::get<int>(this->light_dark_toggle_.getHeight());
    return 24;
}

std::variant<int, stoej::DynamicSize> StatusBar::getWidth() {
    return stoej::DynamicSize::e_fill_parent;
}

void StatusBar::setDP(double dp) {
    this->dp_ = dp;
    //this->light_dark_toggle_.setDP(dp);
    this->help_btn_.setDP(dp);
    //this->oversample_btn_.setDP(dp);
    this->randomize_btn_.setDP(dp);
    this->init_btn_.setDP(dp);
    this->tooltip_box_.setDP(dp);
    //this->preset_text_field_.setDP(dp);
}