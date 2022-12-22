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
#include "gui/components/stoej_xy.h"

class MainGraphic : public stoej::FloatComponent<juce::Component> {
public:
    void paint(juce::Graphics& g) override;
private:
    stoej::XY xy_;
};