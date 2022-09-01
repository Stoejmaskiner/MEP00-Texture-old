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
    getConstrainer()->setFixedAspectRatio(double(WIDTH) / double(HEIGHT));
    getConstrainer()->setMinimumSize(WIDTH * 0.25, HEIGHT * 0.25);

    addAndMakeVisible(this->title_bar_);
    addAndMakeVisible(this->ribbon_);
    addAndMakeVisible(this->main_view_);
    addAndMakeVisible(this->status_bar_);

    setSize (WIDTH * INIT_SCALE, HEIGHT * INIT_SCALE);
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
    auto dp = r.getWidth() / double(WIDTH);

    r.reduce(3*dp, 3*dp);
    this->title_bar_.dp = dp;
	this->title_bar_.setBounds(r.removeFromTop(this->title_bar_.UNSCALED_HEIGHT*dp));
    r.removeFromTop(3*dp);
    this->ribbon_.setBounds(r.removeFromTop(48*dp));
    r.removeFromTop(3*dp);
    this->main_view_.setBounds(r.removeFromTop(168*dp));
    r.removeFromTop(3*dp);
    this->status_bar_.setBounds(r.removeFromTop(24*dp));
    
}
