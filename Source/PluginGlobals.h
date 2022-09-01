/*
  ==============================================================================

    PluginGlobals.h
    Created: 1 Sep 2022 1:59:39am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <string>

static const auto COL_BACKGROUND_PRIMARY   = juce::Colour(254,254,254);
static const auto COL_BACKGROUND_SECONDARY = juce::Colour(238,238,238);
static const auto COL_STROKE_PRIMARY       = juce::Colour(  0,  0,  0);
static const auto COL_STROKE_SECONDARY     = juce::Colour(254,254,254);

static const std::string PRODUCT_TYPE_CODE = "MEP";
static const std::string PRODUCT_NUMBER = "00";
static const std::string PRODUCT_CODE = PRODUCT_TYPE_CODE + PRODUCT_NUMBER;
static const std::string PRODUCT_NAME = "TEXTURE";
// ReSharper disable once StringLiteralTypo
static const std::string COMPANY_NAME = "ST\xc3\x98JMASKINER";
