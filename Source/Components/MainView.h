/*
  ==============================================================================

    MainView.h
    Created: 1 Sep 2022 12:33:37am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MainView  : public juce::Component
{
public:
    MainView();
    ~MainView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainView)
};
