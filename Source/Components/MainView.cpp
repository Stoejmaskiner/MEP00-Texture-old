/*
  ==============================================================================

    MainView.cpp
    Created: 1 Sep 2022 12:33:37am
    Author:  Lorenzo

  ==============================================================================
*/


#include "MainView.h"

#include "gui/components/stoej_button.h"
#include "gui/components/stoej_button.h"
#include "../PluginAssets.h"


//==============================================================================
MainView::MainView() : grit_btn_("grit_btn", stoej::StoejButton::ButtonSize::e_small, "GRIT", get_font_archivo_narrow_light(), true)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(this->bounding_box_);
    //addAndMakeVisible(this->main_widget_);
    addAndMakeVisible(this->spacer_);
    addAndMakeVisible(this->hp_fader_);
    addAndMakeVisible(this->lp_fader_);
    addAndMakeVisible(this->width_fader_);
    addAndMakeVisible(this->level_fader_);
    addAndMakeVisible(this->widget_view_);
    addAndMakeVisible(this->grit_btn_);
    addAndMakeVisible(this->density_val_);
    addAndMakeVisible(this->mix_val_);
    //addAndMakeVisible(this->test_);
    //addAndMakeVisible(this->test2_);
    //this->toggle_button_.setColour(juce::ToggleButton::tickColourId, juce::Colours::black);
    //this->toggle_button_.setToggleable(true);

    //this->test_.setBorderWidth(1.0f);
    //this->test2_.setBorderWidth(1.0f);

	
}

MainView::~MainView()
{
}

void MainView::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    
}

void MainView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto r = getLocalBounds();
    auto rtest = r;
    rtest.reduce(100, 100);
    auto rt1 = rtest.removeFromLeft(50);
    //this->test_.setFloatBounds(juce::Rectangle<float>(rtest.getTopLeft().getX(), rtest.getTopLeft().getY(), rtest.getWidth(), rtest.getHeight()));
    //this->test2_.setFloatBounds(juce::Rectangle<float>(rt1.getTopLeft().getX(), rt1.getTopLeft().getY(), rt1.getWidth(), rt1.getHeight()));

    this->bounding_box_.setBounds(r);
    r.reduce(this->k_padding_ * dp_, this->k_padding_ * dp_);
    auto r1 = r.removeFromLeft(180 * dp_);
    //this->main_widget_.setBounds(r1);  // TODO: get widget width
    this->widget_view_.setBounds(r1.removeFromTop(96 * dp_));
    this->mix_val_.setBounds(r1.removeFromRight(60 * dp_));
    this->density_val_.setBounds(r1.removeFromRight(60 * dp_));

    // TODO: this could be useful as a function
    // centers the button within a larger rectangle (variable padding)
    auto pad_h = (r1.getHeight() / dp_ - 24) / 2 * dp_;
    auto pad_v = (r1.getWidth() / dp_ - 36) / 2 * dp_;
	r1.removeFromTop(pad_h);
    r1.removeFromBottom(pad_h);
    r1.removeFromLeft(pad_v);
    r1.removeFromRight(pad_v);
	
    this->grit_btn_.setFloatBounds(r1);
	this->spacer_.setBounds(r.removeFromLeft(6 * dp_));        // TODO: get width
    this->hp_fader_.setBounds(r.removeFromLeft(48 * dp_));      // TODO: get width
    this->lp_fader_.setBounds(r.removeFromLeft(48 * dp_));      // TODO: get width
    this->width_fader_.setBounds(r.removeFromLeft(48 * dp_));      // TODO: get width
    this->level_fader_.setBounds(r.removeFromLeft(48 * dp_));      // TODO: get width
}

void MainView::setDP(double dp)
{
    this->dp_ = dp;
    this->bounding_box_.setDP(dp);
    this->grit_btn_.setDP(dp);
    //this->test_.setDP(dp);
    //this->test2_.setDP(dp);
}

std::variant<int, stoej::DynamicSize> MainView::getHeight()
{
    // TODO: sum of widget view height and value underneath view
    return 156;
}

std::variant<int, stoej::DynamicSize> MainView::getWidth()
{
    // TODO: sum of everything and spacing
    return 390;
}
