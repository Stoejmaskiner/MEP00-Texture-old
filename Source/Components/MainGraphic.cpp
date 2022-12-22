/*
  ==============================================================================

    MainGraphic.cpp
    Created: 21 Dec 2022 10:37:48pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "MainGraphic.h"



void MainGraphic::paint(juce::Graphics& g)
{
    this->setBorderWidth(1.f);
    this->drawBorder(g);
    this->background_c_ = juce::Colours::black;
    this->drawBackground(g);


}
