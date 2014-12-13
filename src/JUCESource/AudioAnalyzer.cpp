//
//  AudioAnalyzer.cpp
//  JuceProject
//
//  Created by Elska on 11/3/14.
//
//

#include "AudioAnalyzer.h"


AudioAnalyzer::AudioAnalyzer()
{
    setOpaque (true);
    clear();
    
    // set the frame rate
    //startTimer (1000 / 75);
    startTimer (1000 / 1000);
    
    // UI: textBox
    addAndMakeVisible (textBox);
    textBox.setMultiLine (true);
    textBox.setReturnKeyStartsNewLine (true);
    textBox.setReadOnly (true);
    textBox.setScrollbarsShown (true);
    textBox.setCaretVisible (false);
    textBox.setPopupMenuEnabled (true);
    textBox.setColour (TextEditor::backgroundColourId, Colour (0xFFFFFFFF));
    textBox.setColour (TextEditor::outlineColourId, Colour (0x1c000000));
    textBox.setColour (TextEditor::shadowColourId, Colour (0xFFFFFFFF));
    
}

void AudioAnalyzer::paint (Graphics& g)
{
    float sum = 0.0f;
    for (int i = 0; i < 1024; i++)
        sum += samples[i];
    
    //sum /= 1024.0f;
    String str = String(sum);
    
    g.fillAll (Colours::black);
    
    textBox.moveCaretToEnd();
    textBox.insertTextAtCaret ("RMS: " + str + newLine);
}

void AudioAnalyzer::resized()
{
    // UI
    Rectangle<int> r (getLocalBounds().reduced (4));
    textBox.setBounds (r);
}

void AudioAnalyzer::clear()
{
    zeromem (samples, sizeof (samples));
    accumulator = 0;
    subSample = 0;
    iteration = 0;
}

void AudioAnalyzer::audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
                            float** outputChannelData, int numOutputChannels,
                            int numSamples)
{
    for (int i = 0; i < numSamples; ++i)
    {
        float inputSample = 0;
        
        for (int chan = 0; chan < numInputChannels; ++chan){
            if (inputChannelData[chan] != nullptr){
                
                inputSave[chan] = inputChannelData[chan][i];
                inputSample += std::abs (inputChannelData[chan][i]);  // find the sum of all the channels
        
                pushSample (10.0f * inputSample, inputSave, numInputChannels); // boost the level to make it more easily visible.
                
            }
        }
    }
    
    // We need to clear the output buffers before returning, in case they're full of junk..
    for (int j = 0; j < numOutputChannels; ++j){
        if (outputChannelData[j] != nullptr){
            zeromem (outputChannelData[j], sizeof (float) * (size_t) numSamples);
            inputSave[j] = 0;
        }
    }
    
}



void AudioAnalyzer::pushSample (const float newSample, const float (&inputSave)[2], int numChannels)
{
    accumulator += newSample;
    
    if (subSample == 0)
    {
        const int inputSamplesPerPixel = 200;
        
        samples[nextSample] = accumulator / inputSamplesPerPixel;
        nextSample = (nextSample + 1) % numElementsInArray (samples);
        subSample = inputSamplesPerPixel;
        accumulator = 0;
    }
    else
    {
        --subSample;
        
    }
    
    itermod = iteration % (numChannels*100);
    //save to the buffer here
    for (int chan = 0; chan < numChannels; ++chan){
        saveBuf[itermod + chan] = inputSave[chan];
    }
    
    
    if(itermod == 0){//numChannels*100 - 1){
        std::cout << "flag!";
        
        //TO DO: pass the save buff to feature extraction. it will be of size saveBuf[numChannels * 100 * 1024] (i think ?)//
        //but for now
        std::cout << saveBuf << iteration << std::endl;
        
        //set saveBuf to zero
        for(int i = 0; i < (numChannels*100*1024); ++i){
            saveBuf[i] = 0;
        }
    } // end of save to buffer
    
    for(int i = 0; i < numChannels; i++) {
        iteration++; //ensures proper indexing of saveBuf, but necessitates modulo 200 because it is counting twice as fast.
    }
    
}