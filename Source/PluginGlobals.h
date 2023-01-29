/*
  ==============================================================================

    PluginGlobals.h
    Created: 1 Sep 2022 1:59:39am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <string>
#include "version.h"
#include "stoej_core.h"
#include "stoej_properties.h"
#include "JuceHeader.h"

[[deprecated("use arena")]]
static const auto COL_BACKGROUND_PRIMARY   = juce::Colour(254,254,254);

[[deprecated("use arena")]]
static const auto COL_BACKGROUND_SECONDARY = juce::Colour(238,238,238);

[[deprecated("use arena")]]
static const auto COL_STROKE_PRIMARY       = juce::Colour(  0,  0,  0);

[[deprecated("use arena")]]
static const auto COL_STROKE_SECONDARY     = juce::Colour(254,254,254);


const juce::String PRODUCT_CODE = "FP000";
const juce::String PRODUCT_NAME = "TEXTURE";
// ReSharper disable once StringLiteralTypo
const juce::String COMPANY_NAME = juce::CharPointer_UTF8("ST\xc3\x98JMASKINER");

constexpr char APVTS_ID[] = "ohG55G9BQgprztnuX6CHC";


constexpr char VERSION[] = BUILD_VERSION_;
constexpr char BUILD_NUMBER[] = BUILD_BUILD_NUMBER_;




