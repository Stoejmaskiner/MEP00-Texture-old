/*
  ==============================================================================

    PluginAssets.h
    Created: 1 Sep 2022 1:37:10am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

static const juce::Font& get_font_archivo_thin() {
	static juce::Font archivo_thin(
		juce::Font(
			juce::Typeface::createSystemTypefaceFor(
				BinaryData::ArchivoThin_ttf, 
				BinaryData::ArchivoThin_ttfSize)));

	return archivo_thin;
}

static const juce::Font& get_font_archivo_black() {
	static juce::Font archivo_black(
		juce::Font(
			juce::Typeface::createSystemTypefaceFor(
				BinaryData::ArchivoBlack_ttf,
				BinaryData::ArchivoBlack_ttfSize)));

	return archivo_black;
}