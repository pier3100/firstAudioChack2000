cmake_minimum_required(VERSION 3.22)

project(HelloWorldSay VERSION 0.0.1)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# Downloads CPM if not already downloaded. CPM is an easy-to-use package manager nicely integrated with CMake.
include(cmake/cpm.cmake)
# This commands downloads AND configures JUCE. It sets up some variables, like JUCE_SOURCE_DIR.
cpmaddpackage(
  NAME
    JUCE
  GIT_TAG
    8.0.12
  GITHUB_REPOSITORY
    juce-framework/JUCE
  SOURCE_DIR
    ${LIB_DIR}/juce
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME "BusinessBoys"
    PLUGIN_MANUFACTURER_CODE Juce
    PLUGIN_CODE HWSA
    FORMATS VST3 Standalone
    PRODUCT_NAME "FirstPlugin"
)

juce_generate_juce_header(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    source/PluginProcessor.cpp
    source/PluginEditor.cpp
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    juce::juce_audio_utils
  PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)

