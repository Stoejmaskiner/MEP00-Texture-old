/*
  ==============================================================================

    Ribbon.h
    Created: 1 Sep 2022 12:33:19am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Ribbon  : public juce::Component
{
public:
    Ribbon();
    ~Ribbon() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ribbon)
};
