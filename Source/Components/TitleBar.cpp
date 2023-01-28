/*
  ==============================================================================

    TitleBar.cpp
    Created: 1 Sep 2022 12:33:08am
    Author:  Lorenzo

  ==============================================================================
*/


#include "TitleBar.h"
#include "binary_data/stoej_Fonts.h"
#include "utils/stoej_graphics_utils.h"
#include "stoej_APVTS.h"


//==============================================================================
TitleBar::TitleBar(stoej::APVTS* apvts, stoej::ThemeManager& theme_manager) : stoej::FloatComponent<juce::Component>(apvts, theme_manager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

void TitleBar::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    //using namespace stoej::theme_colours;
    //bool use_dark_theme = this->apvts_.getParameterBoolOr(stoej::parameters::internal_use_dark_theme.id, false);

    auto txt_c_1 = this->theme_manager_.getThemeColor(stoej::ThemeManager::text_primary);
    auto txt_c_2 = this->theme_manager_.getThemeColor(stoej::ThemeManager::text_secondary);
    auto r = getLocalFloatBounds();

    
    g.setFont(stoej::get_font_archivo_thin());
    g.setFont (20.f * dp_ * stoej::PT_2_PX);
    g.setColour(txt_c_2);
    g.drawText ("[" + PRODUCT_CODE + "]", r,juce::Justification::left, true);   // draw some placeholder text
    g.setFont(stoej::get_font_archivo_black());
    g.setFont(20.f * dp_ * stoej::PT_2_PX);
    g.setColour(txt_c_1);
    g.drawText (PRODUCT_NAME, r, juce::Justification::right, true);
    auto w = g.getCurrentFont().getStringWidth(PRODUCT_NAME);
    r.removeFromRight(w);
    g.setFont(stoej::get_font_archivo_thin());
    g.setFont(20.0f * dp_ * stoej::PT_2_PX);
    g.drawText(COMPANY_NAME + " // ", r, juce::Justification::right, true);
    
}

void TitleBar::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
