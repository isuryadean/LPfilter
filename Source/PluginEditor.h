#pragma once

#include "PluginProcessor.h"
#include "UI/FilterGraph.h"

//==============================================================================
class LPfilterAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit LPfilterAudioProcessorEditor (LPfilterAudioProcessor&);
    ~LPfilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LPfilterAudioProcessor& processorRef;
    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    FilterGraph filterGraph;

    juce::Slider cutoffSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LPfilterAudioProcessorEditor)
};
