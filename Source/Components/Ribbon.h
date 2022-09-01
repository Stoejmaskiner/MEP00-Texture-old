/*
  ==============================================================================

    Ribbon.h
    Created: 1 Sep 2022 12:33:19am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "gui/components/stoej_box.h"
#include "gui/components/stoej_dbg_box.h"

//==============================================================================
/*
*/
class Ribbon  : public juce::Component, public stoej::IResizableComponent
{
	
public:
    juce::Colour stroke_color = juce::Colour(  0,   0,   0);
    juce::Colour fill_color   = juce::Colour(255, 255, 255);

    Ribbon();
    ~Ribbon() override = default;

    void paint (juce::Graphics&) override;
    void paintOverChildren(juce::Graphics& g) override;
    void resized() override;

    std::variant<int, stoej::DynamicSize> getPreferredHeight() override;
    std::variant<int, stoej::DynamicSize> getPreferredWidth() override;
    void setDP(double dp) override;

private:
    double dp_ = 1.0;
    stoej::Box bounding_box_;
    stoej::DbgBox dbg_box_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ribbon)
};
