//
//  AudioAnalyzer.h
//  JuceProject
//
//
//  Michelle Auyoung, Jordan Juras, Jaeseong You
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
    double inputSave[2];

    void timerCallback() override
    {
        repaint();
    }

    void pushSample (const float newSample, double (&inputSave)[2], int numChannels);

    TextEditor textBox;
    float samplesRMS[1024], samplesZCR[1024];
    int nextSampleRMS, nextSampleZCR, subSample, counterSave, counterBuf, iteration, bufSelect, index, numChannels;
    float accumulatorRMS, accumulatorZCR;

    double saveBuf1[2 * 100 * 1024]; //how big: 100 times writing 1024 samples * numInputChannels(this is not variable yet)
    double saveBuf2[2 * 100 * 1024];
    bool flag;
    typedef double SAMPLE;
    int bufSize = 2 * 100 * 1024;
    int winSize = bufSize/60;
    int hopSize = winSize/2;
    int nCols = 1;
    int nRows = ceil(bufSize/hopSize);
    float sampleRMS;
    float sampleZCR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioAnalyzer);
};



#endif /* defined(__JuceProject__AudioAnalyzer__) */
