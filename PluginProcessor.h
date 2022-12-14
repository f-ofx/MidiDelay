/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DelayNote.h"
#include "SwapNotes.h"
#include "NoteInfo.h"
#include <boost/range/adaptor/indexed.hpp>
using namespace boost::adaptors;
#include <array>

//==============================================================================
/**
*/
class TimeStampAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TimeStampAudioProcessor();
    ~TimeStampAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

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
    
    //```

    
//    using Notes = std::array<NoteInformation, 1000>;
//    Notes noteInfo;
    
    //std::array<noteInformation, 1000> noteInfo;
    //juce::Array<noteInformation> noteInfo;
    
    
    //juce::OwnedArray<noteInformation> noteInfo;
    //std::vector<noteInformation> noteInfo;
    //struct noteInformation noteInfo[20000];
    Notes notes;
    juce::Array<uint> noteBuffer;
//    void process(Notes& notes)
//    {
//    }
//
    //
    
private:
    int sampleCounter = 0;
    DelayNote melodyNote;
    DelayNote delayNote;
    SwapNotes swapNotes;
    juce::MidiBuffer midiBuff;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeStampAudioProcessor)
};


//struct noteData {
//    int velocity;
//    int noteNum;
//};
//
//void setNoteData(noteData &note)
//{
//    note.velocity = 10;
//    note.noteNum = 20;
//    // etc.
//}
