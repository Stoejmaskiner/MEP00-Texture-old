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
    getConstrainer()->setFixedAspectRatio(double(k_width) / double(k_height));
    getConstrainer()->setMinimumSize(k_width, k_height);

    addAndMakeVisible(this->title_bar_);
    addAndMakeVisible(this->ribbon_);
    addAndMakeVisible(this->main_view_);
    addAndMakeVisible(this->status_bar_);

    setSize (k_width * k_init_scale, k_height * k_init_scale);
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
    auto dp = r.getWidth() / double(k_width);

    // IMPORTANT NOTE:
    // only call .setDP from the parent's .setDP method, the top level component (this)
    // is the only exception as it doesn't have a .setDP method.
    this->ribbon_.setDP(dp);
    this->main_view_.setDP(dp);
    this->status_bar_.setDP(dp);

    r.reduce(3*dp, 3*dp);
    this->title_bar_.dp = dp;
	this->title_bar_.setBounds(r.removeFromTop(this->title_bar_.UNSCALED_HEIGHT*dp));
    r.removeFromTop(3*dp);
    this->ribbon_.setBounds(r.removeFromTop(std::get<int>(this->ribbon_.getHeight()) * dp));
    r.removeFromTop(3*dp);
    this->main_view_.setBounds(r.removeFromTop(168*dp));
    r.removeFromTop(3*dp);
    this->status_bar_.setBounds(r.removeFromTop(24*dp));
    r.removeFromLeft(3 * dp);
}
