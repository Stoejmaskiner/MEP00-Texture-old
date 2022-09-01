/*
  ==============================================================================

    TitleBar.cpp
    Created: 1 Sep 2022 12:33:08am
    Author:  Lorenzo

  ==============================================================================
*/


#include "TitleBar.h"

#include "utils/stoej_graphics_utils.h"


//==============================================================================
TitleBar::TitleBar()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

TitleBar::~TitleBar()
{
}

void TitleBar::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    auto r = getLocalBounds();

    g.setColour (COL_STROKE_PRIMARY);
    g.setFont(get_font_archivo_thin());
    g.setFont (20.0f * dp * stoej::PT_2_PX);
    g.drawText ("[" + PRODUCT_CODE + "]", r,juce::Justification::left, true);   // draw some placeholder text
    g.setFont(get_font_archivo_black());
    g.setFont(20.0f * dp * stoej::PT_2_PX);
    g.drawText (PRODUCT_NAME, r, juce::Justification::right, true);
    auto w = g.getCurrentFont().getStringWidth(PRODUCT_NAME);
    r.removeFromRight(w);
    g.setFont(get_font_archivo_thin());
    g.setFont(20.0f * dp * stoej::PT_2_PX);
    g.drawText(COMPANY_NAME + " // ", r, juce::Justification::right, true);
    
}

void TitleBar::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
