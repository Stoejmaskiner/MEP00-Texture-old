/*
  ==============================================================================

    StatusBar.h
    Created: 1 Sep 2022 12:34:07am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class StatusBar  : public juce::Component
{
public:
    StatusBar();
    ~StatusBar() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatusBar)
};
