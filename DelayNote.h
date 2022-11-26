/*
  ==============================================================================

    DelayNote.h
    Created: 25 Nov 2022 5:51:25pm
    Author:  Mouldy Soul

  ==============================================================================
*/
#pragma once
#include "NoteInfo.h"

class DelayNote
{
    public :
    void process(juce::MidiBuffer& midiMessages, int transposeAmount,
                 Notes& notesInfo, int index, int delayValue)
    {
        for (auto message : midiMessages)
        {
            auto currentMessage = message.getMessage();
            auto noteNum = currentMessage.getNoteNumber();
            int velocity = currentMessage.getVelocity();
            int position = message.samplePosition;
            
            if (currentMessage.isNoteOn())
            {
                notePairs.add(noteNum);
                tempOnNote.velocity = velocity;
                tempOnNote.noteNum = noteNum + transposeAmount;
                tempOnNote.position = position;
                tempOnNote.noteOnMsg = true;
                tempOnNote.delay = position + delayValue;
                tempOnNote.delayOff = -1;
                tempOnNote.finishedPlaying = false;
                notesInfo.add(tempOnNote);
                auto nn = notePairs.getLast();
                DBG(juce::String(nn));
            }
            
            if (currentMessage.isNoteOff())
            {
                if (notePairs.contains(noteNum))
                {
                    tempOffNote.noteNum = noteNum + transposeAmount;
                    tempOffNote.position = position;
                    tempOffNote.noteOnMsg = false;
                    tempOffNote.delayOff = position + delayValue;
                    notesInfo.add(tempOffNote);
                    notePairs.remove(noteNum);
                }
            }
        }
    }
    juce::Array<int> notePairs;
    NoteInfo tempOnNote;
    NoteInfo tempOffNote;
};
