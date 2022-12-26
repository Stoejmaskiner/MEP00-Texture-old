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
#include "utils/stoej_math.h"
#include "utils/stoej_luts.h"

class MainGraphic : public stoej::XY {
public:
    MainGraphic();
    void paint(juce::Graphics& g) override;
    juce::Value grit;
};