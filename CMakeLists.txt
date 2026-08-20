cmake_minimum_required(VERSION 3.22)

project(firstVST VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(JUCE)

juce_add_plugin(firstVST
    COMPANY_NAME "Iemanie"

    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE

    PLUGIN_MANUFACTURER_CODE Iemn
    PLUGIN_CODE Fvst

    FORMATS VST3 Standalone
    COPY_PLUGIN_AFTER_BUILD TRUE

    PRODUCT_NAME "firstVST"

    NEEDS_WEB_BROWSER FALSE
    NEEDS_CURL FALSE
)

target_sources(firstVST
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
)

target_compile_definitions(firstVST
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_IGNORE_VST3_MISMATCHED_PARAMETER_ID_WARNING=1
)

target_link_libraries(firstVST
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)