/*
  ==============================================================================

    MainGraphic.cpp
    Created: 21 Dec 2022 10:37:48pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "MainGraphic.h"



MainGraphic::MainGraphic()
{
    this->grit.addListener(this);
}

void MainGraphic::paint(juce::Graphics& g)
{
    this->background_c_ = juce::Colours::black;
    this->drawBackground(g);

    auto r = this->getLocalFloatBounds();
    float x = this->x_range_.convertTo0to1(this->getXValueObject().getValue());
    auto x_pos = x * r.getWidth();
    float y = 1.0f - this->y_range_.convertTo0to1(this->getYValueObject().getValue());
    auto y_pos = y * r.getHeight();

    // TODO: eats CPU, use LUT
    g.setColour(juce::Colours::magenta);
    auto r1 = r;
    r1.reduce(6.f * dp_, 6.f * dp_);
    juce::Path sin_p;
    juce::Path nse_p;
    sin_p.startNewSubPath(r1.getTopLeft().getX(), r1.getTopLeft().getY() * 0.5f + r1.getBottomLeft().getY() * 0.5f);
    float resolution = 128;
    int every_n = 1;
    auto norm_2_bounds = [&](float norm_x, float norm_y) {
        return juce::Point(norm_x * r1.getWidth() + r1.getTopLeft().getX(), (norm_y * -0.5f + 0.5f) * r1.getHeight() + r1.getTopLeft().getY());
    };

    // TODO: this sucks
    // TODO: inefficient
    for (int i = 0; i < resolution; i++) {
        float eval_x = (i + 1) / resolution;
        float eval_y = std::sinf(eval_x * stoej::TAU);
        auto coeffs = stoej::xfade_fast_transition(x);
        sin_p.lineTo(norm_2_bounds(eval_x, eval_y * coeffs.a));
        if (i % every_n == 0) {
            float eval_y_new = stoej::lut_randf_pol[i];
            eval_y_new = eval_y_new < y ? (-y < eval_y_new ? 0.0f : eval_y_new) : eval_y_new;
            eval_y_new = this->grit < 0.5f ? eval_y_new * eval_y : eval_y_new * stoej::clamp_min(eval_y, 0.0f);
            eval_y_new = stoej::xfade(eval_y, eval_y_new, coeffs);
            nse_p.startNewSubPath(norm_2_bounds(eval_x, eval_y * coeffs.a));
            nse_p.lineTo(norm_2_bounds(eval_x, eval_y_new));
        }
    }
    g.strokePath(sin_p, juce::PathStrokeType(2.f * dp_));
    g.strokePath(nse_p, juce::PathStrokeType(1.f * dp_));

    /* TODO: enable this when ready 
    g.setColour(juce::Colours::magenta);
    g.drawVerticalLine(x_pos, 0.f, r.getBottom());
    g.drawHorizontalLine(y_pos, 0.f, r.getRight());
    */

    this->setBorderWidth(1.f);
    this->drawBorder(g);
}
