/*
  ==============================================================================

    MainGraphic.cpp
    Created: 21 Dec 2022 10:37:48pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "MainGraphic.h"



MainGraphic::MainGraphic(stoej::APVTS& apvts, stoej::ThemeManager& theme_manager)
    : stoej::XY(apvts, theme_manager)
{
    this->grit.addListener(this);
}

void MainGraphic::paint(juce::Graphics& g)
{
    //this->background_c_ = juce::Colours::black;
    // TODO:
    //using namespace stoej::theme_colours;
    //bool use_dark_theme = this->apvts_.getParameterBoolOr(stoej::parameters::internal_use_dark_theme.id, false);
    auto bg_c = this->theme_manager_.getThemeColor(stoej::ThemeManager::scope_background);
    this->drawBackground(g, bg_c);

    auto r = this->getLocalFloatBounds();
    float mix = this->x_range_.convertTo0to1(this->getXValueObject().getValue());
    auto x_pos = mix * r.getWidth();
    float density = 1.0f - this->y_range_.convertTo0to1(this->getYValueObject().getValue());
    auto y_pos = density * r.getHeight();

    // TODO: eats CPU
    auto prim_c = this->theme_manager_.getThemeColor(stoej::ThemeManager::fill_primary);
    g.setColour(prim_c);
    auto r1 = r;
    r1.reduce(6.f * dp_, 6.f * dp_);
    juce::Path sin_p;
    juce::Path nse_p;
    sin_p.startNewSubPath(r1.getTopLeft().getX(), r1.getTopLeft().getY() * 0.5f + r1.getBottomLeft().getY() * 0.5f);
    float resolution = 128; // TODO: eco mode reduces this to 64
    auto norm_2_bounds = [&](float norm_x, float norm_y) {
        return juce::Point(norm_x * r1.getWidth() + r1.getTopLeft().getX(), (norm_y * -0.5f + 0.5f) * r1.getHeight() + r1.getTopLeft().getY());
    };

    // TODO: this sucks
    // NOTE: the bottleneck is not sin, but drawing the path, don't bother optimizing for now
    for (int i = 0; i < resolution; i++) {
        auto coeffs = stoej::xfade_fast_transition(mix);
        float x = (i + 1) / resolution;
        float sin_x = std::sinf(x * stoej::TAU);

        // noise from fixed LUT
        float nse_x = stoej::lut_randf_pol[i];
        
        // apply density transform to noise
        nse_x = nse_x < density ? (-density < nse_x ? 0.0f : nse_x) : nse_x;

        // apply grit transform to noise
        nse_x = this->grit < 0.5f ? nse_x * sin_x : nse_x * stoej::clamp_min(sin_x, 0.0f);

        nse_x = stoej::xfade(sin_x, nse_x, coeffs);
        nse_x = stoej::clamp_abs(nse_x, 1.05f);
        sin_p.lineTo(norm_2_bounds(x, sin_x * coeffs.a));
        nse_p.startNewSubPath(norm_2_bounds(x, sin_x * coeffs.a));
        nse_p.lineTo(norm_2_bounds(x, nse_x));
    }
    g.strokePath(sin_p, juce::PathStrokeType(2.f * dp_));
    g.strokePath(nse_p, juce::PathStrokeType(1.f * dp_));

    /* TODO: enable this when ready 
    g.setColour(juce::Colours::magenta);
    g.drawVerticalLine(x_pos, 0.f, r.getBottom());
    g.drawHorizontalLine(y_pos, 0.f, r.getRight());
    */

    auto border_c = this->theme_manager_.getThemeColor(stoej::ThemeManager::foreground_primary);
    this->drawBorder(g, 1.f, border_c);
}
