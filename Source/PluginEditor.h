#pragma once

#include "PluginProcessor.h"

//==============================================================================
class LPfilterAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit LPfilterAudioProcessorEditor (LPfilterAudioProcessor&);
    ~LPfilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LPfilterAudioProcessor& processorRef;
    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    juce::Slider cutoffSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LPfilterAudioProcessorEditor)
};
