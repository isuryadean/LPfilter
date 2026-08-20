#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstVSTAudioProcessorEditor::FirstVSTAudioProcessorEditor (FirstVSTAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(gainSlider);

    gainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);

    gainSlider.setTextBoxStyle(
        juce::Slider::TextBoxBelow,
        false,
        60,
        20);
    
    gainAttachment = std::make_unique<
        juce::AudioProcessorValueTreeState::SliderAttachment>(
            processorRef.parameters,
            "gain",
            gainSlider);

    setSize (400, 300);
}

FirstVSTAudioProcessorEditor::~FirstVSTAudioProcessorEditor()
{
}

//==============================================================================
void FirstVSTAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("This jawn loud", getLocalBounds(), juce::Justification::centred, 1);
}

void FirstVSTAudioProcessorEditor::resized()
{
    gainSlider.setBounds(100, 50, 200, 200);
}
