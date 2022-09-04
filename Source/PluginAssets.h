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
		juce::Typeface::createSystemTypefaceFor(
			BinaryData::ArchivoThin_ttf, 
			BinaryData::ArchivoThin_ttfSize));

	return archivo_thin;
}

static const juce::Font& get_font_archivo_black() {
	static juce::Font archivo_black(
		juce::Typeface::createSystemTypefaceFor(
			BinaryData::ArchivoBlack_ttf,
			BinaryData::ArchivoBlack_ttfSize));

	return archivo_black;
}

static const juce::Font& get_font_archivo_narrow_light() {
	static juce::Font archivo_narrow_light(
		juce::Typeface::createSystemTypefaceFor(
			BinaryData::Archivo_CondensedLight_ttf,
			BinaryData::Archivo_CondensedLight_ttfSize));

	return archivo_narrow_light;
}

static const juce::Font& get_font_archivo_narrow_bold() {
	static juce::Font archivo_narrow_bold(
		juce::Typeface::createSystemTypefaceFor(
			BinaryData::Archivo_CondensedBold_ttf,
			BinaryData::Archivo_CondensedBold_ttfSize));

	return archivo_narrow_bold;
}