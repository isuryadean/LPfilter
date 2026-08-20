#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <array>

//==============================================================================
class LPfilterAudioProcessor final : public juce::AudioProcessor
{
public:
    //==============================================================================
    LPfilterAudioProcessor();
    ~LPfilterAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState parameters;

    double getSampleRate() const { return sampleRate; }

    //FFT stuff
    static constexpr int fftOrder = 11;
    static constexpr int fftSize = 1 << fftOrder;

    const std::array<float, fftSize / 2>& getSpectrum() const
    {
        return spectrum;
    }

private:
    //==============================================================================
    float previousSample[2] = { 0.0f, 0.0f };
    double sampleRate = 44100.0;

    //FFT stuff
    juce::dsp::FFT fft { fftOrder };
    std::array<float, fftSize * 2> fftData {};
    int fftIndex = 0;
    std::array<float, fftSize / 2> spectrum {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LPfilterAudioProcessor)

};
