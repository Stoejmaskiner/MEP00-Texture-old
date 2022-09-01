/*
  ==============================================================================

    Ribbon.cpp
    Created: 1 Sep 2022 12:33:19am
    Author:  Lorenzo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Ribbon.h"

//==============================================================================
Ribbon::Ribbon()
{
    this->addAndMakeVisible(this->bounding_box_);
    this->addAndMakeVisible(this->dbg_box_);
}


void Ribbon::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

   



    
}

void Ribbon::paintOverChildren(juce::Graphics& g) {
	Component::paintOverChildren(g);
    g.setColour(juce::Colours::black);
    g.setFont(14.0f);
    g.drawText("Ribbon", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text
}

void Ribbon::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto r = this->getLocalBounds();
    this->bounding_box_.setBounds(r);
    r.reduce(12*this->dp_,12*this->dp_);
    this->dbg_box_.setBounds(r);

}

std::variant<int, stoej::DynamicSize> Ribbon::getPreferredHeight() {
    return 48;
}

std::variant<int, stoej::DynamicSize> Ribbon::getPreferredWidth() {
	return stoej::DynamicSize::e_fill_parent;
}

void Ribbon::setDP(double dp) {
    this->dp_ = dp;
    this->bounding_box_.setDP(dp);
}
