/*
  ==============================================================================

    Ribbon.cpp
    Created: 1 Sep 2022 12:33:19am
    Author:  Lorenzo

  ==============================================================================
*/

// TODO(Lorenzo) make this DRYer by introducing a ComponentArray class
//
// see issue #1 in shared-code

#include <JuceHeader.h>
#include "Ribbon.h"

//==============================================================================
Ribbon::Ribbon() :
    burger_menu_btn_(this->list_ico_),
    browse_presets_btn_(this->folder_ico_),
	previous_preset_btn_(this->left_ico_),
	next_preset_btn_(this->right_ico_),
	save_preset_btn_(this->floppy_ico_)
{
    // setting edge visibility to avoid redrawing adjacent edges
    this->burger_menu_btn_.setTilePosition(stoej::e_array_left);
    this->browse_presets_btn_.setTilePosition(stoej::e_array_horizontal);
    this->previous_preset_btn_.setTilePosition(stoej::e_array_horizontal);
    this->next_preset_btn_.setTilePosition(stoej::e_array_horizontal);
    this->save_preset_btn_.setTilePosition(stoej::e_array_horizontal);

    //this->addAndMakeVisible(this->bounding_box_);
    this->addAndMakeVisible(this->dbg_box_);
    this->addAndMakeVisible(this->burger_menu_btn_);
    this->addAndMakeVisible(this->browse_presets_btn_);
    this->addAndMakeVisible(this->previous_preset_btn_);
    this->addAndMakeVisible(this->next_preset_btn_);
    this->addAndMakeVisible(this->save_preset_btn_);
    this->addAndMakeVisible(this->light_dark_theme_tgl_);
}


void Ribbon::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
}

void Ribbon::paintOverChildren(juce::Graphics& g) {
	Component::paintOverChildren(g);
    g.setColour(juce::Colours::black);
    g.setFont(14.0f);
    g.drawText("Ribbon", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text
}

void Ribbon::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto r = this->getLocalBounds();
    //this->bounding_box_.setBounds(r);
    //r.reduce(12*this->dp_,12*this->dp_);
    //this->dbg_box_.setBounds(r);

    // left hand buttons
    this->burger_menu_btn_.setBounds(
        r.removeFromLeft(std::get<int>(this->burger_menu_btn_.getWidth()) * dp_));
    this->browse_presets_btn_.setBounds(
        r.removeFromLeft(std::get<int>(this->browse_presets_btn_.getWidth()) * dp_));
    this->previous_preset_btn_.setBounds(
        r.removeFromLeft(std::get<int>(this->previous_preset_btn_.getWidth()) * dp_));
    this->next_preset_btn_.setBounds(
        r.removeFromLeft(std::get<int>(this->next_preset_btn_.getWidth()) * dp_));
    
    // right hand buttons
    this->light_dark_theme_tgl_.setBounds(
        r.removeFromRight(std::get<int>(this->save_preset_btn_.getWidth()) * dp_));
    this->save_preset_btn_.setBounds(
        r.removeFromRight(std::get<int>(this->save_preset_btn_.getWidth()) * dp_));
    
    // text box
    this->dbg_box_.setBounds(r);
}

std::variant<int, stoej::DynamicSize> Ribbon::getHeight() {
    // TODO(Lorenzo) when shared-code/#1 is implemented, this should automatically
    // determine the height of the ribbon based on the height of the child component array
    //
    // the component array should refuse inconsistent component sizes and return the
    // size of its children when queried.
    return 24;
}

std::variant<int, stoej::DynamicSize> Ribbon::getWidth() {
	return stoej::DynamicSize::e_fill_parent;
}

void Ribbon::setDP(double dp) {
    this->dp_ = dp;
    this->burger_menu_btn_.setDP(dp);
    this->browse_presets_btn_.setDP(dp);
    this->previous_preset_btn_.setDP(dp);
    this->next_preset_btn_.setDP(dp);
    this->save_preset_btn_.setDP(dp);
    //this->bounding_box_.setDP(dp);
}
