/*
  ==============================================================================

    PluginParameters.h
    Created: 30 Aug 2022 2:43:45pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <utils/stoej_juce_utils.h>

// Huh?
// This is a way of adding static analysis to parameter IDs because I was tired
// of getting mysterious nullptr exceptions when making a typo



namespace Parameters {
	inline constexpr stoej::BoolParamInfo  enable_grit {"ENABLE_GRIT", "grit", false};
	inline constexpr stoej::FloatParamInfo noise_density { .id = "NOISE_DENSITY", .name = "noise density", .init = 1.0f, .range_0 = 0.00002f, .skew = .2f};
	inline constexpr stoej::FloatParamInfo noise_mix{ .id = "NOISE_MIX", .name = "mix", .init = 0.5f, .range_0 = 0.0f, .range_1 = 1.0f, .skew = 1.0f};
	inline constexpr stoej::FloatParamInfo filter_lp_cutoff { .id = "FILTER_LP_CUTOFF", .name = "LP cutoff", .init = 12000.0f, .range_0 = 20.0f, .range_1 = 20000.0f, .skew = 0.25f};
	inline constexpr stoej::FloatParamInfo filter_hp_cutoff { .id = "FILTER_HP_CUTOFF", .name = "HP cutoff", .init = 120.0f, .range_0 = 20.0f, .range_1 = 20000.0f, .skew = 0.25f };
	inline constexpr stoej::FloatParamInfo noise_width{ "NOISE_WIDTH", "noise width", 1.0f };
	inline constexpr stoej::FloatParamInfo output_level{ .id = "OUTPUT_LEVEL", .name = "output level", .init = 1.0f, .range_0 = 0.0f, .range_1 = 2.0f, .skew = 0.5f };
}

// BEGIN STATIC TESTS
// making sure parameters are actually constexpr
static_assert(Parameters::enable_grit.init == false);
static_assert(Parameters::filter_lp_cutoff.use_symmetric_skew == false);
// END STATIC TESTS