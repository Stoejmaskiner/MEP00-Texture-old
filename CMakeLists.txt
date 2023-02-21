# TODO: make it possible to build this without the
# plugins repository

# This is the name of your plugin
# This cannot have spaces (but PRODUCT_NAME can)
set(PROJECT_NAME "FEP00_Texture")

# Set the plugin formats you'll be building here.
# Valid formats: AAX Unity VST AU AUv3 Standalone
set(FORMATS AU AUv3 VST VST3)

# Reads in VERSION file and sticks in it CURRENT_VERSION variable
# Be sure the file has no newlines
file(STRINGS VERSION CURRENT_VERSION)

# For simplicity, the name of the project is also the name of the target
project(${PROJECT_NAME} VERSION ${CURRENT_VERSION})

# Check the readme at `docs/CMake API.md` in the JUCE repo for full config
juce_add_plugin(
    ${PROJECT_NAME}
    COMAPNY_NAME ${manufacturer}
    BUNDLE_ID ${bundle_id}
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE ${manufacturer_code}
    PLUGIN_CODE F000
    FORMATS ${FORMATS}
    PRODUCT_NAME ${PROJECT_NAME})

target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_23)

target_sources(
    "${PROJECT_NAME}"
    PRIVATE
    src/PluginEditor.h
    src/PluginProcessor.h
    src/PluginEditor.cpp
    src/PluginProcessor.cpp)

# hmm...
set_target_properties("${PROJECT_NAME}" PROPERTIES FOLDER "")

set(JUCE_DEPENDENCIES
    juce::juce_audio_utils)

target_compile_definitions(
    "${PROJECT_NAME}"
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP=1)

target_link_libraries(
    "${PROJECT_NAME}"
    PRIVATE
    ${JUCE_DEPENDENCIES}
    PUBLIC
    stoej_core
    stoej_dsp
    stoej_gui
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags)