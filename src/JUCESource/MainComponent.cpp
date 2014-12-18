//
//  MainComponent.cpp
//  JuceProject
//
//
//  Michelle Auyoung, Jordan Juras, Jaeseong You
//
//

#include "MainComponent.h"


MainComponent::MainComponent() //will need to call the system class data
{
    
    if(analyzer.getflag() == 0){
        std::cout << "FLAG CHECK !!!!" << std::endl; //for future implementation 
    }
    
    
    setOpaque (true);
    
    // create a device manager and connect it to the modules
    deviceManager = new AudioDeviceManager();
    deviceManager->initialise (2, 2, 0, true, String::empty, 0);
    
    
    addAndMakeVisible (liveAudioScroller);
    deviceManager->addAudioCallback (&liveAudioScroller);
    
    addAndMakeVisible (analyzer);
    deviceManager->addAudioCallback (&analyzer);
    
    // UI: quitButton
    addAndMakeVisible(quitButton = new TextButton(String::empty));
    quitButton->setButtonText("Quit");
    quitButton->addListener(this);
    
    
    // set size of the window
    setSize(600,600);
    
    /*bThread[0] = new BeaconThread("Thread1");
    bThread[1] = new BeaconThread("Thread2");
    bThread[2] = new BeaconThread("Thread3");
    bThread[3] = new BeaconThread("Thread4");
    
    for (int i=0; i<4; i++)
        bThread[i]->startThread();*/
}

MainComponent::~MainComponent()
{
    // clean up
    label = nullptr;
    quitButton = nullptr;
    deviceManager->removeAudioCallback(&liveAudioScroller);
    deviceManager->removeAudioCallback(&analyzer);
}

void MainComponent::fillBrushedAluminiumBackground (Graphics& g)
{
    // create background color
    g.setFillType (FillType (ImageCache::getFromMemory (BinaryData::brushed_aluminium_png,
                                                        BinaryData::brushed_aluminium_pngSize),
                             AffineTransform::identity));
    g.fillAll();
}

void MainComponent::paint(Graphics& g)
{
    // set background color
    fillBrushedAluminiumBackground (g);
}

void MainComponent::resized()
{
    // UI size and location
    Rectangle<int> area (getLocalBounds());
    liveAudioScroller.setBounds (area.removeFromTop (80).reduced (8));
    analyzer.setBounds (area.removeFromTop (160).reduced (8));
    quitButton->setBounds(getWidth()-176, getHeight()-60, 120, 32);

}

void MainComponent::buttonClicked(Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == quitButton)
        JUCEApplication::quit();
}