//
//  MainComponent.h
//  JuceProject
//
//
//  Michelle Auyoung, Jordan Juras, Jaeseong You
//
//

#ifndef __JuceProject__MainComponent__
#define __JuceProject__MainComponent__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../JuceLibraryCode/BinaryData.h"

#include "AudioLiveScrollingDisplay.h"
#include "AudioAnalyzer.h"
#include "BeaconThread.h"




class MainComponent: public Component, public ButtonListener
{
public:
    MainComponent();
    ~MainComponent();
    
    void paint (Graphics& g);
    void resized();
    void buttonClicked(Button* buttonThatWasClicked);
    void fillBrushedAluminiumBackground (Graphics& g);
    
private:
    ScopedPointer<Label> label;
    ScopedPointer<TextButton> quitButton;
    AudioDeviceManager *deviceManager;
    LiveScrollingAudioDisplay liveAudioScroller;
    AudioAnalyzer analyzer;
    
    //BeaconThread *bThread[4];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};


#endif /* defined(__JuceProject__MainComponent__) */
