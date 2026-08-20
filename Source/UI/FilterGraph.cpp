#include "FilterGraph.h"

FilterGraph::FilterGraph()
{
}

void FilterGraph::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    auto graph = getLocalBounds().reduced (20);

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

    for (auto frequency : frequencyValues)
    {
        auto x = frequencyToX (frequency);
        g.drawHorizontalLine (
            juce::roundToInt (x),
            (float) graph.getY(),
            (float) graph.getBottom());
        g.drawText (
            juce::string(frequency),
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
        g.drawVerticalLine (
            juce::roundToInt (y),
            (float) graph.getX(),
            (float) graph.getRight());
        g.drawText (
            juce::string(decibels),
            graph.getX() - 40,
            juce::roundToInt (y) - 10,
            30,
            20,
            juce::Justification::centred);
    }
}

void FilterGraph::resized()
{
}