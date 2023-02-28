# this configuration is based on pamplejuce: https://github.com/sudara/pamplejuce/blob/main/CMakeLists.txt
# used under the terms of the MIT license

cmake_minimum_required(VERSION 3.24.1)

# This is the name of your plugin
# This cannot have spaces (but PRODUCT_NAME can)
set(PROJECT_NAME "FEP00_Texture")

# Adds all the module sources so they appear correctly in the IDE
# Must be set before JUCE is added as a sub-dir (or any targets are made)
# https://github.com/juce-framework/JUCE/commit/6b1b4cf7f6b1008db44411f2c8887d71a3348889
set_property(GLOBAL PROPERTY USE_FOLDERS YES)

add_subdirectory(libs/JUCE)

# Set the plugin formats you'll be building here.
# Valid formats: AAX Unity VST AU AUv3 Standalone
set(FORMATS AU AUv3 VST VST3)
juce_set_vst2_sdk_path("C:\\VST_SDK\\vst2sdk\\vstsdk2.4")   # TODO: make this parametric and optional

# Reads in VERSION file and sticks in it CURRENT_VERSION variable
# Be sure the file has no newlines
file(STRINGS VERSION CURRENT_VERSION)

# For simplicity, the name of the project is also the name of the target
project(${PROJECT_NAME} VERSION ${CURRENT_VERSION})

# By default we don't want Xcode schemes to be made for modules, etc
set(CMAKE_XCODE_GENERATE_SCHEME OFF)

# TODO: hmmm...
# # Building universal binaries on macOS increases build time
# # This is set on CI but not during local dev
# if ((DEFINED ENV{CI}) AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
#   message("Building for Apple Silicon and x86_64")
#   set(CMAKE_OSX_ARCHITECTURES arm64 x86_64)
# endif ()

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Support macOS down to High Sierra")

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

target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_20)

target_sources(
    "${PROJECT_NAME}"
    PRIVATE
    src/PluginEditor.h
    src/PluginProcessor.h
    src/PluginEditor.cpp
    src/PluginProcessor.cpp)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    FP000_PRODUCT_CODE="FP000"
)

# No, we don't want our source buried in extra nested folders
set_target_properties("${PROJECT_NAME}" PROPERTIES FOLDER "")

# The Xcode source tree should uhhh, still look like the source tree, yo
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Source PREFIX "" FILES ${SourceFiles})

# TODO: hmmm...
# # Setup our binary data as a target
# juce_add_binary_data(Assets SOURCES pamplejuce.png)

# TODO: hmmm...
# # Required for Linux happiness:
# # See https://forum.juce.com/t/loading-pytorch-model-using-binarydata/39997/2
# set_target_properties(Assets PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

# Clean up folder organization on Xcode.
# It tucks the Plugin varieties into a "Targets" folder and generate an Xcode Scheme manually
# Xcode scheme generation is turned off globally to limit noise from other targets
# The non-hacky way of doing this is via the global PREDEFINED_TARGETS_FOLDER property
# However that doesn't seem to be working in Xcode
# Not all plugin types (au, vst) available on each build type (win, macos, linux)
foreach(target ${FORMATS} "All")
    if(TARGET ${PROJECT_NAME}_${target})
        set_target_properties(${PROJECT_NAME}_${target} PROPERTIES
            # Tuck the actual plugin targets into a folder where they won't bother us
            FOLDER "Targets"

            # MacOS only: Sets the default executable that Xcode will open on build
            # For this exact path to to work, manually build the AudioPluginHost.xcodeproj in the JUCE subdir
            XCODE_SCHEME_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/libs/JUCE/extras/AudioPluginHost/Builds/MacOSX/build/Debug/AudioPluginHost.app"

            # Let us build the target in Xcode
            XCODE_GENERATE_SCHEME ON)
    endif()
endforeach()
# TODO: hmmm...
#set_target_properties(Assets PROPERTIES FOLDER "Targets")

set(JUCE_DEPENDENCIES
    juce::juce_core
    juce::juce_audio_utils
    juce::juce_audio_processors)
juce_add_modules(
    libs/stoej_core
    libs/stoej_gui)

target_compile_definitions(
    "${PROJECT_NAME}"
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0)

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

# TODO: hmmm...
# # When present, use Intel IPP for performance on Windows
# if(MSVC)
#     find_package(IPP)
#     if(IPP_FOUND)
#         target_link_libraries("${PROJECT_NAME}" PUBLIC IPP::ipps IPP::ippcore IPP::ippi IPP::ippcv)
#         message("IPP LIBRARIES FOUND")
#         target_compile_definitions("${PROJECT_NAME}" PUBLIC PAMPLEJUCE_IPP=1)
#     else()
#         message("IPP LIBRARIES *NOT* FOUND")
#     endif()
# endif()

# TODO: hmmm...
# # Required for ctest (which is just easier for cross-platform CI)
# # include(CTest) does this too, but adds tons of targets we don't want
# # See: https://github.com/catchorg/Catch2/issues/2026
# # You also could forgo ctest and call ./Tests directly from the build dir
# enable_testing()

# # "GLOBS ARE BAD" is brittle and silly dev UX, sorry CMake!
# # CONFIGURE_DEPENDS / Clion's CMake integration makes globbing absolutely fine
# file(GLOB_RECURSE TestFiles CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h")
# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/tests PREFIX "" FILES ${TestFiles})

# # Use Catch2 v3 on the devel branch
# Include(FetchContent)
# FetchContent_Declare(
#     Catch2
#     GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#     GIT_PROGRESS TRUE
#     GIT_SHALLOW TRUE
#     GIT_TAG v3.1.0)
# FetchContent_MakeAvailable(Catch2) # find_package equivalent

# # Our test executable also wants to know about our plugin code...
# target_include_directories(Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)
# target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain "${PROJECT_NAME}" ${JUCE_DEPENDENCIES})

# # Make an Xcode Scheme for the test executable so we can run tests in the IDE
# set_target_properties(Tests PROPERTIES XCODE_GENERATE_SCHEME ON)

# # Organize the test source in the Tests/ folder in the IDE
# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Tests PREFIX "" FILES ${TestFiles})

# # Load and use the .cmake file provided by Catch2
# # https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md
# # We have to manually provide the source directory here for now
# include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)
# catch_discover_tests(Tests)

# # Setup the test executable, again C++ 20 please
# add_executable(tests ${TestFiles})
# target_compile_features(tests PRIVATE cxx_std_20)

# Color our warnings and errors
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   add_compile_options (-fcolor-diagnostics)
endif ()