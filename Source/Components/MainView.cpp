/*
  ==============================================================================

    MainView.cpp
    Created: 1 Sep 2022 12:33:37am
    Author:  Lorenzo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainView.h"

//==============================================================================
MainView::MainView()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(this->bounding_box_);
    addAndMakeVisible(this->main_widget_);
    addAndMakeVisible(this->spacer_);
    addAndMakeVisible(this->hp_fader_);
    addAndMakeVisible(this->lp_fader_);
    addAndMakeVisible(this->width_fader_);
    addAndMakeVisible(this->level_fader_);
}

MainView::~MainView()
{
}

void MainView::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

}

void MainView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto r = getLocalBounds();
    this->bounding_box_.setBounds(r);
    r.reduce(this->k_padding_ * dp_, this->k_padding_ * dp_);
    this->main_widget_.setBounds(r.removeFromLeft(180 * dp_));  // TODO: get widget width
    this->spacer_.setBounds(r.removeFromLeft(6 * dp_));        // TODO: get width
    this->hp_fader_.setBounds(r.removeFromLeft(48 * dp_));      // TODO: get width
    this->lp_fader_.setBounds(r.removeFromLeft(48 * dp_));      // TODO: get width
    this->width_fader_.setBounds(r.removeFromLeft(48 * dp_));      // TODO: get width
    this->level_fader_.setBounds(r.removeFromLeft(48 * dp_));      // TODO: get width
}

void MainView::setDP(double dp)
{
    this->dp_ = dp;
    this->bounding_box_.setDP(dp);
}

std::variant<int, stoej::DynamicSize> MainView::getHeight()
{
    // TODO: sum of widget view height and value underneath view
    return 156;
}

std::variant<int, stoej::DynamicSize> MainView::getWidth()
{
    // TODO: sum of everything and spacing
    return 390;
}
