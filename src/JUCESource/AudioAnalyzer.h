//
//  AudioAnalyzer.h
//  JuceProject
//
//  Created by Elska on 11/3/14.
//
//

#ifndef __JuceProject__AudioAnalyzer__
#define __JuceProject__AudioAnalyzer__

#include "../JuceLibraryCode/JuceHeader.h"

class AudioAnalyzer
    : public Component, public AudioIODeviceCallback, private Timer
{
public:
    AudioAnalyzer();
    //~AudioAnalyzer();
    
    void audioDeviceAboutToStart (AudioIODevice*) override
    {
        clear();
    }

    void audioDeviceStopped() override
    {
        clear();
    }

    void audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
                                float** outputChannelData, int numOutputChannels,
                                int numSamples) override;
bool getflag();

private:
    void clear();
    void paint (Graphics& g) override;
    void resized() override;
    float inputSave[2];

    void timerCallback() override
    {
        repaint();
    }

    void pushSample (const float newSample, const float (&inputSave)[2], int numChannels);

    TextEditor textBox;
    float samples[1024];
    int nextSample, subSample, counterSave, counterBuf, iteration, bufSelect, index, numChannels;
    float accumulator;

    float saveBuf1[2 * 100 * 1024]; //how big: 100 times writing 1024 samples * numInputChannels(this is not variable yet)
    float saveBuf2[2 * 100 * 1024];
    bool flag; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioAnalyzer);
};



#endif /* defined(__JuceProject__AudioAnalyzer__) */
