//
//  MainComponent.h
//  JuceProject
//
//  Created by Elska on 11/3/14.
//
//

#ifndef __JuceProject__MainComponent__
#define __JuceProject__MainComponent__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../JuceLibraryCode/BinaryData.h"

#include "AudioLiveScrollingDisplay.h"
#include "AudioAnalyzer.h"
#include "BeaconThread.h"
//#include "FeatureController.h"



class MainComponent: public Component, public ButtonListener
{
public:
    MainComponent();
    ~MainComponent();
    
    void paint (Graphics& g);
    void resized();
    void buttonClicked(Button* buttonThatWasClicked);
    void fillBrushedAluminiumBackground (Graphics& g);
    
    
    //void func();
    
private:
    ScopedPointer<Label> label;
    ScopedPointer<TextButton> quitButton;
    AudioDeviceManager *deviceManager;
    LiveScrollingAudioDisplay liveAudioScroller;
    AudioAnalyzer analyzer;
    
    //TRY: liveAudioScroller2;
    LiveScrollingAudioDisplay liveAudioScroller2;
    
    BeaconThread *bThread[4];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};


#endif /* defined(__JuceProject__MainComponent__) */
