/*
  ==============================================================================

    MainGraphic.h
    Created: 21 Dec 2022 10:37:48pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "gui/components/stoej_component.h"

class MainGraphic : public stoej::FloatComponent<juce::Component> {
    void paint(juce::Graphics& g) override;
};