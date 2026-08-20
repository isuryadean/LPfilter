#include "FilterGraph.h"

FilterGraph::FilterGraph (LPfilterAudioProcessor& p): processorRef (p)
{
    startTimerHz (30);
}

void FilterGraph::paint (juce::Graphics& g)
{
    auto graph = getLocalBounds().reduced (30,20);

    g.setColour (juce::Colours::grey);

    // Graph outline
    g.drawRect (graph);

    //Draw X Axis - Frequency
    const float minFreq = 20.0f;
    const float maxFreq = 20000.0f;
    const float frequencyValues[] =
    {
        20.0f,
        100.0f,
        1000.0f,
        10000.0f,
        20000.0f

    };

    // Convert frequency to an X position
    auto frequencyToX = [graph, minFreq, maxFreq] (float frequency)
    {
        auto normalised =
            std::log10 (frequency / minFreq) / std::log10 (maxFreq / minFreq);

        return graph.getX()
             + normalised * graph.getWidth();
    };

    //change boring freqiuency to K and kHz
    auto frequencyToString = [] (float frequency)
    {
        if (frequency >= 1000.0f)
            return juce::String (frequency / 1000.0f, 0) + " kHz";

        return juce::String (frequency, 0) + " Hz";
    };

    for (auto frequency : frequencyValues)
    {
        auto x = frequencyToX (frequency);
        g.drawVerticalLine (
            juce::roundToInt (x),
            (float) graph.getY(),
            (float) graph.getBottom());
        g.drawText (
            frequencyToString(frequency),
            juce::roundToInt (x) - 15,
            graph.getBottom() - 20,
            30,
            20,
            juce::Justification::centred);
    }

    //Draw Y Axis - Decibels
    const float minDb = -36.0f;
    const float maxDb = 0.0f;
    const float decibelValues[] =
    {
        0.0f,
        -6.0f,
        -12.0f,
        -18.0f,
        -24.0f,
        -30.0f,
        -36.0f
    };
    //convert decibels to a Y pos
    auto decibelsToY = [graph, minDb, maxDb] (float decibels)
    {
        auto normalised = (decibels - minDb) / (maxDb - minDb);
        return graph.getBottom()
            - normalised * graph.getHeight();
    };

    g.setColour (juce::Colours::lightgrey);

    for (auto decibels : decibelValues)
    {
        auto y = decibelsToY (decibels);
        g.drawHorizontalLine (
            juce::roundToInt (y),
            (float) graph.getX(),
            (float) graph.getRight());
        g.drawText (
            juce::String(decibels),
            graph.getX() - 40,
            juce::roundToInt (y) - 10,
            30,
            20,
            juce::Justification::centred);
    }

    //Filter Curve
    auto cutoff = processorRef.parameters.getRawParameterValue ("cutoff")->load();
    const int numPoints = 200;
    juce::Path filterCurve;
    const float sampleRate = static_cast<float> (processorRef.getSampleRate());
    auto alpha = 1.0f - std::exp (
            -2.0f * juce::MathConstants<float>::pi * cutoff / sampleRate);
    for (int i = 0; i < numPoints; ++i)
    {
        auto normalised = static_cast<float> (i) / (numPoints - 1);
        auto frequency = minFreq * std::pow (maxFreq / minFreq, normalised);

        // We'll calculate the filter response here
        auto omega =
            2.0f * juce::MathConstants<float>::pi
            * frequency
            / sampleRate;

        auto magnitude =
            alpha /
            std::sqrt (
                1.0f
                - 2.0f * (1.0f - alpha) * std::cos (omega)
                + (1.0f - alpha) * (1.0f - alpha));

        auto responseDb = 20.0f * std::log10 (magnitude);
        auto x = frequencyToX (frequency);
        auto y = decibelsToY (responseDb);
        if (i == 0)
            filterCurve.startNewSubPath (x, y);
        else
            filterCurve.lineTo (x, y);
    }
    g.setColour (juce::Colours::black);
    g.strokePath (
        filterCurve,
        juce::PathStrokeType (2.0f));

    //FFT spectrum analyser
    auto& spectrum = processorRef.getSpectrum();

    juce::Path spectrumPath;

    for (int i = 1; i < LPfilterAudioProcessor::fftSize / 2; ++i)
    {
        auto frequency =
            static_cast<float> (i)
            * static_cast<float> (processorRef.getSampleRate())
            / static_cast<float> (LPfilterAudioProcessor::fftSize);

        if (frequency < minFreq || frequency > maxFreq)
            continue;

        auto magnitude = spectrum[i];

        auto magnitudeDb =
            juce::Decibels::gainToDecibels (
                magnitude / static_cast<float> (LPfilterAudioProcessor::fftSize));

        // Keep the spectrum inside our graph
        magnitudeDb = juce::jlimit (minDb, maxDb, magnitudeDb);

        auto x = frequencyToX (frequency);
        auto y = decibelsToY (magnitudeDb);

        if (spectrumPath.isEmpty())
            spectrumPath.startNewSubPath (x, y);
        else
            spectrumPath.lineTo (x, y);
    }

    g.setColour (juce::Colours::darkgrey);

    g.strokePath (
        spectrumPath,
        juce::PathStrokeType (1.5f));
    }

void FilterGraph::resized()
{
}

void FilterGraph::timerCallback()
{
    repaint();
}