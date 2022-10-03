/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
MEP00TextureAudioProcessorEditor::MEP00TextureAudioProcessorEditor (MEP00TextureAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setResizable(true,true);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    getConstrainer()->setFixedAspectRatio(double(k_width_) / double(k_height_));
    getConstrainer()->setMinimumSize(k_width_, k_height_);

    addAndMakeVisible(this->title_bar_);
    addAndMakeVisible(this->ribbon_);
    addAndMakeVisible(this->main_view_);
    addAndMakeVisible(this->status_bar_);

    setSize (k_width_ * k_init_scale_, k_height_ * k_init_scale_);
}

MEP00TextureAudioProcessorEditor::~MEP00TextureAudioProcessorEditor()
{
}

//==============================================================================
void MEP00TextureAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (COL_BACKGROUND_SECONDARY);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

	
}

void MEP00TextureAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto r = getLocalBounds();
    auto dp = r.getWidth() / double(k_width_);
    auto inner_width = std::get<int>(this->main_view_.getWidth());

    // IMPORTANT NOTE:
    // only call .setDP from the parent's .setDP method, the top level component (this)
    // is the only exception as it doesn't have a .setDP method.
    this->ribbon_.setDP(dp);
    this->main_view_.setDP(dp);
    this->status_bar_.setDP(dp);

    // form main layout
    r.removeFromTop(this->k_padding_ * dp);
    r.removeFromLeft(this->k_padding_ * dp);
    r = r.removeFromLeft(inner_width * dp);
    
    this->title_bar_.dp = dp;
	this->title_bar_.setBounds(r.removeFromTop(this->title_bar_.UNSCALED_HEIGHT*dp));
    r.removeFromTop(this->k_padding_ * dp);
    //this->ribbon_.setBounds(r.removeFromTop(std::get<int>(this->ribbon_.getHeight()) * dp));
    //r.removeFromTop(3*dp);
    this->main_view_.setBounds(r.removeFromTop(std::get<int>(this->main_view_.getHeight()) * dp));
    r.removeFromTop(this->k_padding_ * dp);
    this->status_bar_.setBounds(r.removeFromTop(std::get<int>(this->status_bar_.getHeight()) * dp));
    r.removeFromLeft(this->k_padding_ * dp);
}
