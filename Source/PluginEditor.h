/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/TitleBar.h"
#include "utils/stoej_graphics.h"

class Box : public juce::Component {
	void paint(juce::Graphics& g) override {
		auto r =getLocalBounds();

        g.setColour(juce::Colour(255, 255, 255));
        g.fillAll();
        g.setColour(juce::Colour(0,0,0));
        g.drawRect(r);
	};
};

//==============================================================================
/**
*/
class MEP00TextureAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MEP00TextureAudioProcessorEditor (MEP00TextureAudioProcessor&);
    ~MEP00TextureAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    static constexpr int WIDTH = 414;
    static constexpr int HEIGHT = 277;
    static constexpr double INIT_SCALE = 1.5;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MEP00TextureAudioProcessor& audioProcessor;
    TitleBar title_bar_;
    Box ribbon_;
    Box main_view_;
    Box status_bar_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MEP00TextureAudioProcessorEditor)
};
