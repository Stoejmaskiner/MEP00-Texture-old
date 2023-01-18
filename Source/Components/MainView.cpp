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
#include "binary_data/stoej_Fonts.h"
#include "../PluginAssets.h"


//==============================================================================
MainView::MainView(juce::AudioProcessorValueTreeState& apvts) :
    widget_view_(apvts),
    grit_btn_(apvts, "grit_btn", stoej::StoejButton::ButtonSize::small, "GRIT", true),
    mix_val_(apvts, Parameters::noise_mix.id, "MIX", stoej::ValueUnit::percent),
    density_val_(apvts, Parameters::noise_density.id, "DENSITY", stoej::ValueUnit::percent),
    lp_fader_(apvts, "lp_fader", "LP", stoej::ValueUnit::hertz, false),
    hp_fader_(apvts, "hp_fader", "HP", stoej::ValueUnit::hertz, true),
    width_fader_(apvts, Parameters::noise_width.id, "WIDTH", stoej::ValueUnit::percent, false),
    level_fader_(apvts, Parameters::output_level.id, "LEVEL", stoej::ValueUnit::level2db, false)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(this->bounding_box_);
    //addAndMakeVisible(this->main_widget_);
    //addAndMakeVisible(this->spacer_);
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

    // TODO: macro this, or see other TODO about putting this inside components
    this->mix_val_attachment_.reset(
        new SliderAttach(apvts, Parameters::noise_mix.id, this->mix_val_)
    );
    this->density_val_attachment_.reset(
        new SliderAttach(apvts, Parameters::noise_density.id, this->density_val_)
    );
    this->hp_fader_attachment_.reset(
        new SliderAttach(apvts, Parameters::filter_hp_cutoff.id, this->hp_fader_)
    );
    this->lp_fader_attachment_.reset(
        new SliderAttach(apvts, Parameters::filter_lp_cutoff.id, this->lp_fader_)
    );
    this->width_fader_attachment_.reset(
        new SliderAttach(apvts, Parameters::noise_width.id, this->width_fader_)
    );
    this->level_fader_attachment_.reset(
        new SliderAttach(apvts, Parameters::output_level.id, this->level_fader_)
    );
    this->grit_btn_attachment_.reset(
        new ButtonAttach(apvts, Parameters::enable_grit.id, this->grit_btn_)
    );

    this->widget_view_.getXValueObject().referTo(this->mix_val_.getValueObject());
    this->widget_view_.setXRange(apvts.getParameterRange(Parameters::noise_mix.id));
    this->widget_view_.getYValueObject().referTo(this->density_val_.getValueObject());
    this->widget_view_.setYRange(apvts.getParameterRange(Parameters::noise_density.id));
    this->widget_view_.grit.referTo(this->grit_btn_.getToggleStateValue());
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
    auto r_main = getLocalBounds();
    auto rtest = r_main;
    rtest.reduce(100, 100);
    auto rt1 = rtest.removeFromLeft(50);
    //this->test_.setFloatBounds(juce::Rectangle<float>(rtest.getTopLeft().getX(), rtest.getTopLeft().getY(), rtest.getWidth(), rtest.getHeight()));
    //this->test2_.setFloatBounds(juce::Rectangle<float>(rt1.getTopLeft().getX(), rt1.getTopLeft().getY(), rt1.getWidth(), rt1.getHeight()));

    this->bounding_box_.setBounds(r_main);
    r_main.reduce(this->k_padding_ * dp_, this->k_padding_ * dp_);
    auto r1_main = r_main.removeFromLeft(180 * dp_);
    //this->main_widget_.setBounds(r1);  // TODO: get widget width
    this->widget_view_.setFloatBounds(r1_main.removeFromTop(96 * dp_));
    this->mix_val_.setFloatBounds(r1_main.removeFromRight(60 * dp_));
    this->density_val_.setFloatBounds(r1_main.removeFromRight(60 * dp_));

    // TODO: this could be useful as a function
    // TODO: use the preferred width and height of the button
    // TODO: pretty sure there is already a method in Rectangle for this
    // centers the button within a larger rectangle (variable padding)
    auto pad_h = (r1_main.getHeight() / dp_ - 24.f) / 2.f * dp_;
    auto pad_v = (r1_main.getWidth() / dp_ - 36.f) / 2.f * dp_;
	r1_main.removeFromTop(pad_h);
    r1_main.removeFromBottom(pad_h);
    r1_main.removeFromLeft(pad_v);
    r1_main.removeFromRight(pad_v);
	
    this->grit_btn_.setFloatBounds(r1_main);
	r_main.removeFromLeft(6.f * dp_);        // TODO: get width
    this->hp_fader_.setFloatBounds(r_main.removeFromLeft(48 * dp_));      // TODO: get width
    this->lp_fader_.setFloatBounds(r_main.removeFromLeft(48 * dp_));      // TODO: get width
    this->width_fader_.setFloatBounds(r_main.removeFromLeft(48 * dp_));      // TODO: get width
    this->level_fader_.setFloatBounds(r_main.removeFromLeft(48 * dp_));      // TODO: get width
}

void MainView::setDP(double dp)
{
    this->dp_ = dp;
    this->widget_view_.setDP(dp);
    this->bounding_box_.setDP(dp);
    this->mix_val_.setDP(dp);
    this->density_val_.setDP(dp);
    this->grit_btn_.setDP(dp);
    this->hp_fader_.setDP(dp);
    this->lp_fader_.setDP(dp);
    this->width_fader_.setDP(dp);
    this->level_fader_.setDP(dp);
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
