#include <juce_gui_extra/juce_gui_extra.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    chooseFileButton.onClick = [this] { chooseFile(); };
    addAndMakeVisible (chooseFileButton);

    pathLabel.setJustificationType (juce::Justification::left);
    pathLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    pathLabel.setText (processorRef.getSamplerPath(), juce::dontSendNotification);
    addAndMakeVisible (pathLabel);

    setSize (400, 120);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

void AudioPluginAudioProcessorEditor::chooseFile()
{
    auto chooser = std::make_shared<juce::FileChooser> ("Select a sample file");

    chooser->launchAsync (juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
                           [this, chooser] (const juce::FileChooser& fc)
                           {
                               auto file = fc.getResult();
                               if (file.existsAsFile())
                               {
                                   processorRef.setSamplerPath (file.getFullPathName());
                                   pathLabel.setText (processorRef.getSamplerPath(), juce::dontSendNotification);
                               }
                           });
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (16);
    chooseFileButton.setBounds (area.removeFromTop (32));
    pathLabel.setBounds (area.removeFromTop (32));
}
