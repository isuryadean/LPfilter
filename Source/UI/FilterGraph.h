#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "../PluginProcessor.h"

class FilterGraph : public juce::Component, private juce::Timer
{
public:
    FilterGraph (LPfilterAudioProcessor& p);
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    void timerCallback() override;
    LPfilterAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGraph)
};