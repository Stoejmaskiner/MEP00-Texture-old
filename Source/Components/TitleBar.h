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

//==============================================================================
/*
*/
class TitleBar  : public juce::Component
{
public:
    static constexpr int UNSCALED_HEIGHT = 22;
    double dp = 1.0;
    TitleBar();
    ~TitleBar() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TitleBar)
};
