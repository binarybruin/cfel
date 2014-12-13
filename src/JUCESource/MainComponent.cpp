//
//  MainComponent.cpp
//  JuceProject
//
//  Created by Elska on 11/3/14.
//
//

#include "MainComponent.h"

/*
#include "../../../src/sharedDSP/FeatureExtraction/SpectralFeatureExtractor.h"
#include "../../../src/sharedDSP/FeatureExtraction/TemporalFeatureExtractor.h"
#include "../../../src/sharedDSP/FeatureExtraction/Utils/EuclidDist.h"
#include "../../../src/sharedDSP/FeatureExtraction/Utils/FFT.h"
#include "../../../src/sharedDSP/FeatureExtraction/Utils/WindowFunction.h"
#include "../../../src/sharedDSP/FeatureExtraction/Utils/OouraFFT.h"

enum FeatureID {
    FEATURE_RMS = 0,
    FEATURE_SPEC_CENT,	// NB: Hanning-windowed
    FEATURE_SPEC_FLUX,	// NB: Hanning-windowed
    FEATURE_FFT,		// NB: Use FFT with caution as it outputs tons of numbers
    FEATURE_RAW,		// NB: Use raw signal with caution as it outputs tons of numbers
    FEATURE_OOURAFFT,	// NB: Use OOURAFFT with caution as it outputs tons of numbers
    NUM_FEATURES
};

char FeatureName[NUM_FEATURES][40] = {
    "RMS",
    "SPEC_CENT",
    "SPEC_FLUX",
    "SPEC_FFT",
    "Raw Signal"
};

void MainComponent::func()
{
    FeatureID featID = FEATURE_RMS;
    double fs = 44100.0;
    int bufSize = 1024;
    int hopSize = bufSize/2;
    double freq = 880.0;
    double dur = 1.0;
    double amp = 0.5;
    double noise = 0.0;
    
    // Display info
    printf("Extracting %s, fs: %.0f, bufSize: %d, hopSize: %d\n", FeatureName[featID], fs, bufSize, hopSize);
    printf("freq: %.2f Hz, dur: %.2f secs, amp: %.2f, noise: %.2f\n", freq, dur, amp, noise);
    
    // Init
    double dt = 1.0/fs;
    double buffer[bufSize];
    int pointer = 0;
    
    // Generate signal
    for(double t=0.0; t<dur; t+=dt) {
        buffer[pointer++] = amp*sin(2.0*M_PI*freq*t) + noise*(rand()/double(RAND_MAX)*2.0-1.0);
        
        // When buffer is full
        if(pointer == bufSize) {
            // Extract and display
            switch(featID) {
                case FEATURE_RMS: {
                    double rms = FeatureExtraction::TemporalFeatureExtractor::calculateRMS(buffer, bufSize);
                    printf("%f ", rms);
                    break;
                }
                    
                case FEATURE_SPEC_CENT: {
                    vector<double> win = FeatureExtraction::SpectralFeatureExtractor::windowSamples(buffer, bufSize, FeatureExtraction::Utils::WINDOW_TYPE_HANNING);
                    vector<double> fft = FeatureExtraction::SpectralFeatureExtractor::calculateFFT(&win[0], win.size());
                    double speccent = FeatureExtraction::SpectralFeatureExtractor::calculateSpecCent(&fft[0], fft.size(), fs/bufSize);
                    printf("%f ", speccent);
                    break;
                }
                    
                case FEATURE_SPEC_FLUX: {
                    vector<double> win = FeatureExtraction::SpectralFeatureExtractor::windowSamples(buffer, bufSize, FeatureExtraction::Utils::WINDOW_TYPE_HANNING);
                    vector<double> fft = FeatureExtraction::SpectralFeatureExtractor::calculateFFT(&win[0], win.size());
                    double specflux = FeatureExtraction::SpectralFeatureExtractor::calculateSpecFlux(&fft[0], fft.size());
                    printf("%f ", specflux);
                    break;
                }
                    
                case FEATURE_FFT: {
                    vector<double> fft = FeatureExtraction::SpectralFeatureExtractor::calculateFFT(buffer, bufSize);
                    for(int i=0; i<fft.size(); ++i)
                        printf("%f ", fft[i]);
                    printf(";\n");
                    break;
                }
                    
                case FEATURE_RAW: {
                    for(int i=0; i<bufSize; ++i)
                        printf("%f ", buffer[i]);
                    printf(";\n");
                    break;
                }
                    
                case FEATURE_OOURAFFT: {
                    OouraFFT *offt = new OouraFFT(bufSize, bufSize, 0);
                    vector<double> fft = offt->calculateMagSpectrum(buffer);
                    //printf("fft.size()=%d\n",(int)fft.size());
                    for(int i=0; i<fft.size(); ++i)
                        printf("%f ", fft[i]);
                    printf(";\n");
                    delete offt;
                    break;
                }
                    
                default:
                    break;
            }
            
            // Hop
            std::copy(buffer+hopSize, buffer+bufSize, buffer);
            pointer = bufSize-hopSize;
            
            // for raw signal or FFT only print out the first frame
            if (featID==FEATURE_FFT || featID==FEATURE_RAW || featID==FEATURE_OOURAFFT)
                break;
        }
    }
    
    printf("\n");
}
*/

MainComponent::MainComponent() //will need to call the system class data
{
    
    //func();           this will be the system class constructor
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
    
    bThread[0] = new BeaconThread("Manhatten");
    bThread[1] = new BeaconThread("Queens");
    bThread[2] = new BeaconThread("Brooklyn");
    bThread[3] = new BeaconThread("Bronx");
    
    for (int i=0; i<4; i++)
        bThread[i]->startThread();
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