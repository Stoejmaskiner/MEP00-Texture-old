/*
  ==============================================================================

    TitleBar.h
    Created: 1 Sep 2022 12:33:08am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../PluginAssets.h"
#include "../PluginGlobals.h"
#include "utils/stoej_graphics_utils.h"
#include "gui/components/stoej_component.h"

//==============================================================================
/*
*/
class TitleBar  : public stoej::FloatComponent<juce::Component>
{
public:
    //static constexpr int UNSCALED_HEIGHT = 22;

    TitleBar(stoej::ThemedAPVTS& apvts);
    std::variant<float, stoej::DynamicSize2> getPreferredHeight() override { return { 22.0f }; }
    std::variant<float, stoej::DynamicSize2> getPreferredWidth() override { return { stoej::fill_parent }; }
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TitleBar)
};
