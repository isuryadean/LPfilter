#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LPfilterAudioProcessorEditor::LPfilterAudioProcessorEditor (LPfilterAudioProcessor& p)
    : AudioProcessorEditor (&p), 
    processorRef (p),
    filterGraph (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    //GainSlider
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(
        juce::Slider::TextBoxBelow,
        false,
        60,
        20);
    gainSlider.setColour (juce::Slider::textBoxBackgroundColourId, juce::Colours::darkslategrey);
    gainSlider.setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    gainSlider.setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    gainAttachment = std::make_unique<
        juce::AudioProcessorValueTreeState::SliderAttachment>(
            processorRef.parameters,
            "gain",
            gainSlider);

    //CutoffSlider
    addAndMakeVisible(cutoffSlider);
    cutoffSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    cutoffSlider.setTextBoxStyle(
        juce::Slider::TextBoxBelow,
        false,
        60,
        20);
    cutoffSlider.setColour (juce::Slider::textBoxBackgroundColourId, juce::Colours::darkslategrey);
    cutoffSlider.setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    cutoffSlider.setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    cutoffAttachment = std::make_unique<
        juce::AudioProcessorValueTreeState::SliderAttachment>(
            processorRef.parameters,
            "cutoff",
            cutoffSlider);
    
    //Graph
    addAndMakeVisible(filterGraph);
        

    setSize (700, 500);
}

LPfilterAudioProcessorEditor::~LPfilterAudioProcessorEditor()
{
}

//==============================================================================
void LPfilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

}

void LPfilterAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (20);

    // Graph
    filterGraph.setBounds (
        area.removeFromTop (320));

    // Controls get whatever is left
    auto controls = area;

    gainSlider.setBounds (
        controls.removeFromLeft (150)
                .withSizeKeepingCentre (120, 120));

    cutoffSlider.setBounds (
        controls.removeFromRight (150)
                .withSizeKeepingCentre (120, 120));
}
