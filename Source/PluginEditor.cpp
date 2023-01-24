/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "utils/stoej_juce_utils.h"



//==============================================================================
MEP00TextureAudioProcessorEditor::MEP00TextureAudioProcessorEditor (MEP00TextureAudioProcessor& p, stoej::ThemedAPVTS& apvts)
    : 
    AudioProcessorEditor (&p), 
    audioProcessor (p), 
    widget_view_(apvts),
    light_dark_toggle_(
        apvts,
        "light_dark_toggle", 
        stoej::StoejButton::tiny, 
        STOEJ_DRAWABLE_IMG(stoej_BinaryData::moonlight_svg),
        STOEJ_DRAWABLE_IMG(stoej_BinaryData::sundimlight_svg)), 
    help_btn_(
        apvts,
        "help_btn",
        stoej::StoejButton::tiny,
        STOEJ_DRAWABLE_IMG(stoej_BinaryData::bookopenlight_svg)),
    //oversample_btn_(
    //    apvts,
    //    "oversample_btn",
    //    stoej::StoejButton::tiny,
    //    STOEJ_DRAWABLE_IMG(stoej_BinaryData::gaugelight_svg)),
    randomize_btn_(
        apvts,
        "randomize_btn",
        stoej::StoejButton::tiny,
        STOEJ_DRAWABLE_IMG(stoej_BinaryData::shuffleangularlight_svg)),
    init_btn_(
        apvts,
        "init_btn",
        stoej::StoejButton::ButtonSize::tiny,
        STOEJ_DRAWABLE_IMG(stoej_BinaryData::filepluslight_svg)),
    tooltip_box_(apvts, "tooltip_box"),
    //grit_btn_("grit_btn", stoej::StoejButton::ButtonSize::small, "GRIT", true),
    grit_btn_(apvts, "grit_btn", stoej::StoejButton::ButtonSize::small, "GRIT", true),
    mix_val_(apvts, Parameters::noise_mix.id, "MIX", stoej::ValueUnit::percent),
    density_val_(apvts, Parameters::noise_density.id, "DENSITY", stoej::ValueUnit::percent),
    lp_fader_(apvts, "lp_fader", "LP", stoej::ValueUnit::hertz, false),
    hp_fader_(apvts, "hp_fader", "HP", stoej::ValueUnit::hertz, true),
    width_fader_(apvts, Parameters::noise_width.id, "WIDTH", stoej::ValueUnit::percent, false),
    level_fader_(apvts, Parameters::output_level.id, "LEVEL", stoej::ValueUnit::level2db, false),
    apvts_(apvts),
    title_bar_(apvts)
{
    
    setResizable(true,true);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    getConstrainer()->setFixedAspectRatio(double(k_width_) / double(k_height_));
    getConstrainer()->setMinimumSize(k_width_, k_height_);

    addAndMakeVisible(this->title_bar_);
    //addAndMakeVisible(this->ribbon_);
    //addAndMakeVisible(this->main_view_);
    //addAndMakeVisible(this->status_bar_);

    //this->help_btn_.setTilePosition(stoej::e_array_horizontal);
    //this->oversample_btn_.setTilePosition(stoej::e_array_horizontal);
    //this->randomize_btn_.setTilePosition(stoej::e_array_horizontal);
    //this->init_btn_.setTilePosition(stoej::e_array_horizontal);
    //  this->preset_text_field_.setTilePosition(stoej::e_array_horizontal);

      //this->addAndMakeVisible(this->preset_text_field_);
    this->addAndMakeVisible(this->light_dark_toggle_);
    this->addAndMakeVisible(this->help_btn_);
    //this->addAndMakeVisible(this->oversample_btn_);
    this->addAndMakeVisible(this->randomize_btn_);
    this->addAndMakeVisible(this->init_btn_);
    this->addAndMakeVisible(this->tooltip_box_);

    //this->light_dark_toggle_.setTooltip("gneurshk");
    //this->light_dark_toggle_.addMouseListener(&this->tooltip_box_, false);

    //addAndMakeVisible(this->bounding_box_);
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
    this->light_dark_toggle_attachment_.reset(
        new ButtonAttach(apvts, stoej::bool_params.at(stoej::strings::internal_params::use_dark_theme).id, this->light_dark_toggle_)
    );

    // TODO: handle this with custom APVTS attachments instead (can you even attach two things to the same parameter?)
    this->widget_view_.getXValueObject().referTo(this->mix_val_.getValueObject());
    this->widget_view_.setXRange(apvts.getParameterRange(Parameters::noise_mix.id));
    this->widget_view_.getYValueObject().referTo(this->density_val_.getValueObject());
    this->widget_view_.setYRange(apvts.getParameterRange(Parameters::noise_density.id));
    this->widget_view_.grit.referTo(this->grit_btn_.getToggleStateValue());

    // set all the tooltips
    // TODO: use ParameterInfo to store the tooltips
    #define ADD_TOOLTIP_(c,s,box) \
    c.setTooltip(s); \
    c.addMouseListener(&box, false);
    ADD_TOOLTIP_(this->grit_btn_, "adds asymmetric distortion to the noise", this->tooltip_box_);
    ADD_TOOLTIP_(this->density_val_, "low density = crackle, high density = hiss", this->tooltip_box_);
    ADD_TOOLTIP_(this->mix_val_, "blend unprocessed input with texture noise", this->tooltip_box_);
    ADD_TOOLTIP_(this->hp_fader_, "high-pass filter the texture noise (12 dB/oct)", this->tooltip_box_);
    ADD_TOOLTIP_(this->lp_fader_, "low-pass filter the texture noise (12 dB/oct)", this->tooltip_box_);
    ADD_TOOLTIP_(this->width_fader_, "stereo width of the texture noise", this->tooltip_box_);
    ADD_TOOLTIP_(this->level_fader_, "main volume of the output", this->tooltip_box_);
    ADD_TOOLTIP_(this->help_btn_, "open the manual (in your browser)", this->tooltip_box_);
    #undef ADD_TOOLTIP_

    this->help_btn_.onClick = []() { juce::URL("https://www.youtube.com/watch?v=dQw4w9WgXcQ").launchInDefaultBrowser(); };
    this->init_btn_.onClick = [&apvts]() {
        stoej::apvts_reset_param(apvts, Parameters::enable_grit.id);
        stoej::apvts_reset_param(apvts, Parameters::filter_hp_cutoff.id);
        stoej::apvts_reset_param(apvts, Parameters::filter_lp_cutoff.id);
        stoej::apvts_reset_param(apvts, Parameters::noise_density.id);
        stoej::apvts_reset_param(apvts, Parameters::noise_mix.id);
        stoej::apvts_reset_param(apvts, Parameters::noise_width.id);
        stoej::apvts_reset_param(apvts, Parameters::output_level.id);
    };
    this->randomize_btn_.onClick = [&apvts]() {
        stoej::apvts_random_param(apvts, Parameters::enable_grit.id);
        stoej::apvts_random_param(apvts, Parameters::filter_hp_cutoff.id);
        stoej::apvts_random_param(apvts, Parameters::filter_lp_cutoff.id);
        stoej::apvts_random_param(apvts, Parameters::noise_density.id);
        stoej::apvts_random_param(apvts, Parameters::noise_mix.id);
        stoej::apvts_random_param(apvts, Parameters::noise_width.id);
        stoej::apvts_random_param(apvts, Parameters::output_level.id);
    };
    this->light_dark_toggle_.addListener(this);
    /*
    this->light_dark_toggle_.onClick = [&apvts, parent = this]() {
        bool old_state = apvts.state.getProperty("use_dark_theme", false);
        bool new_state = 
        juce::String s_old_state = old_state ? "true" : "false";
        juce::String s_new_state = new_state ? "true" : "false";
        DBG("PluginEditor: toggled dark theme, from=<" << s_old_state << ">, to=<" << s_new_state << ">");
        apvts.state.setProperty("use_dark_theme", new_state, nullptr);
    };
    */

    auto internal_properties = this->apvts_.state.getChildWithName(stoej::strings::apvts_children::internal_properties_state);
    jassert(internal_properties.isValid());
    float init_scale = internal_properties.getProperty(stoej::properties.at(stoej::strings::internal_properties::gui_scale).id);
    DBG("PluginEditor: init_scale=<" + std::to_string(init_scale) + ">");
    jassert(init_scale > 0);
    setSize (k_width_ * init_scale, k_height_ * init_scale);
}
        
MEP00TextureAudioProcessorEditor::~MEP00TextureAudioProcessorEditor()
{
}

//==============================================================================
void MEP00TextureAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    auto internal_properties_state = this->apvts_.state.getChildWithName(stoej::strings::apvts_children::internal_properties_state);
    float dp = internal_properties_state.getProperty(stoej::properties.at(stoej::strings::internal_properties::gui_scale).id);


    auto bg_c_1 = this->apvts_.getGenericThemeColorWithModeApplied(stoej::strings::generic_theme::background_primary);
    auto bg_c_2 = this->apvts_.getGenericThemeColorWithModeApplied(stoej::strings::generic_theme::background_secondary);
    auto border_c = this->apvts_.getGenericThemeColorWithModeApplied(stoej::strings::generic_theme::foreground_primary);
    auto r = this->getLocalBounds().toFloat();
    g.fillAll (bg_c_2);

    g.setColour(bg_c_1);
    stoej::fill_rect_f(g, this->inner_r);

    //DBG("PluginEditor: painting border with color border_c=<" + border_c.toString() + ">, thickness dp=<" + std::to_string(dp) + ">");
    g.setColour(border_c);
    stoej::draw_rect_f(g, this->inner_r, 1.f * dp);
}

void MEP00TextureAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto r = this->getLocalBounds().toFloat();
    auto dp = r.getWidth() / double(k_width_);
    auto internal_properties = this->apvts_.state.getChildWithName(stoej::strings::apvts_children::internal_properties_state);
    jassert(internal_properties.isValid());
    internal_properties.setProperty(stoej::properties.at(stoej::strings::internal_properties::gui_scale).id, dp, nullptr);
    double inner_width = 390.0;

    // IMPORTANT NOTE:
    // only call .setDP from the parent's .setDP method, the top level component (this)
    // is the only exception as it doesn't have a .setDP method.
    //this->ribbon_.setDP(dp);
    //this->main_view_.setDP(dp);
    this->light_dark_toggle_.setDP(dp);
    this->help_btn_.setDP(dp);
    //this->oversample_btn_.setDP(dp);
    this->randomize_btn_.setDP(dp);
    this->init_btn_.setDP(dp);
    this->tooltip_box_.setDP(dp);
    this->widget_view_.setDP(dp);
    //this->bounding_box_.setDP(dp);
    this->mix_val_.setDP(dp);
    this->density_val_.setDP(dp);
    this->grit_btn_.setDP(dp);
    this->hp_fader_.setDP(dp);
    this->lp_fader_.setDP(dp);
    this->width_fader_.setDP(dp);
    this->level_fader_.setDP(dp);

    // form main layout
    r.removeFromTop(this->k_padding_ * dp);
    r.removeFromLeft(this->k_padding_ * dp);
    r = r.removeFromLeft(inner_width * dp);
    
    this->title_bar_.setDP(dp);
    // TODO: title with FloatComponent
	this->title_bar_.setFloatBounds(r.removeFromTop(std::get<float>(this->title_bar_.getPreferredHeight()) * dp));
    r.removeFromTop(this->k_padding_ * dp);
    //this->ribbon_.setBounds(r.removeFromTop(std::get<int>(this->ribbon_.getHeight()) * dp));
    //r.removeFromTop(3*dp);
    //this->main_view_.setBounds(r.removeFromTop(std::get<int>(this->main_view_.getHeight()) * dp));
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto r_main = r.removeFromTop(156 * dp);
    auto rtest = r_main;
    rtest.reduce(100, 100);
    auto rt1 = rtest.removeFromLeft(50);
    //this->test_.setFloatBounds(juce::Rectangle<float>(rtest.getTopLeft().getX(), rtest.getTopLeft().getY(), rtest.getWidth(), rtest.getHeight()));
    //this->test2_.setFloatBounds(juce::Rectangle<float>(rt1.getTopLeft().getX(), rt1.getTopLeft().getY(), rt1.getWidth(), rt1.getHeight()));

    // TODO: use float rect for bounding box
    this->inner_r = r_main;
    r_main.reduce(this->k_padding_2 * dp, this->k_padding_2 * dp);
    auto r1_main = r_main.removeFromLeft(180 * dp);
    //this->main_widget_.setBounds(r1);  // TODO: get widget width
    this->widget_view_.setFloatBounds(r1_main.removeFromTop(96 * dp));
    this->mix_val_.setFloatBounds(r1_main.removeFromRight(60 * dp));
    this->density_val_.setFloatBounds(r1_main.removeFromRight(60 * dp));

    // TODO: this could be useful as a function
    // TODO: use the preferred width and height of the button
    // TODO: pretty sure there is already a method in Rectangle for this
    // centers the button within a larger rectangle (variable padding)
    auto pad_h = (r1_main.getHeight() / dp - 24.f) / 2.f * dp;
    auto pad_v = (r1_main.getWidth() / dp - 36.f) / 2.f * dp;
    //r1_main.removeFromTop(pad_h);
    //r1_main.removeFromBottom(pad_h);
    //r1_main.removeFromLeft(pad_v);
    //r1_main.removeFromRight(pad_v);
    r1_main.reduce(pad_v, pad_h);

    this->grit_btn_.setFloatBounds(r1_main);
    r_main.removeFromLeft(6.f * dp);        // TODO: get width
    this->hp_fader_.setFloatBounds(r_main.removeFromLeft(48 * dp));      // TODO: get width
    this->lp_fader_.setFloatBounds(r_main.removeFromLeft(48 * dp));      // TODO: get width
    this->width_fader_.setFloatBounds(r_main.removeFromLeft(48 * dp));      // TODO: get width
    this->level_fader_.setFloatBounds(r_main.removeFromLeft(48 * dp));      // TODO: get width
    
    r.removeFromTop(this->k_padding_ * dp);
    auto r1 = r.removeFromTop(24 * dp);
    // TODO: this is atrocious, please implement a component array of some kind!
    this->light_dark_toggle_.setFloatBounds(
        r1.removeFromLeft(std::get<float>(this->light_dark_toggle_.getPreferredWidth()) * dp));

    this->help_btn_.setFloatBounds(
        r1.removeFromLeft(std::get<float>(this->help_btn_.getPreferredWidth()) * dp));

    //this->oversample_btn_.setFloatBounds(
    //    r1.removeFromLeft(std::get<float>(this->oversample_btn_.getPreferredWidth()) * dp));

    this->randomize_btn_.setFloatBounds(
        r1.removeFromLeft(std::get<float>(this->randomize_btn_.getPreferredWidth()) * dp));

    this->init_btn_.setFloatBounds(
        r1.removeFromLeft(std::get<float>(this->init_btn_.getPreferredWidth()) * dp));

    this->tooltip_box_.setFloatBounds(r1);
    r.removeFromLeft(this->k_padding_ * dp);
}


// TODO: maybe make a LightDarkThemeToggleHandler class to clearly denote what this method does?
void MEP00TextureAudioProcessorEditor::buttonClicked(juce::Button* b) {
    DBG("theme_handler: button=<" + b->getName() + "> was clicked");
    // TODO: store ids in string arena
    if (b->getName() == "light_dark_toggle") {
        DBG("theme_handler: repainting");
        this->repaint();
    }
}