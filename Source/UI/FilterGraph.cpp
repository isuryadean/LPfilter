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

    const float minFreq = 20.0f;
    const float maxFreq = 20000.0f;

    // Convert frequency to an X position
    auto frequencyToX = [graph, minFreq, maxFreq] (float frequency)
    {
        auto normalised =
            std::log10 (frequency / minFreq)
            / std::log10 (maxFreq / minFreq);

        return graph.getX()
             + normalised * graph.getWidth();
    };

    // Temporary frequency markers
    g.drawVerticalLine (
        frequencyToX (20.0f),
        (float) graph.getY(),
        (float) graph.getBottom());

    g.drawVerticalLine (
        frequencyToX (100.0f),
        (float) graph.getY(),
        (float) graph.getBottom());

    g.drawVerticalLine (
        frequencyToX (1000.0f),
        (float) graph.getY(),
        (float) graph.getBottom());

    g.drawVerticalLine (
        frequencyToX (10000.0f),
        (float) graph.getY(),
        (float) graph.getBottom());

    g.drawVerticalLine (
        frequencyToX (20000.0f),
        (float) graph.getY(),
        (float) graph.getBottom());
}

void FilterGraph::resized()
{
}