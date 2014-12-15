//
//  AudioAnalyzer.cpp
//  JuceProject
//
//  Created by Elska on 11/3/14.
//
//

#include "AudioAnalyzer.h"
//#include "FeatureController.h"


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
    textBox.insertTextAtCaret ("RMS:EDIT: " + str + newLine);
}

void AudioAnalyzer::resized()
{
    // UI
    Rectangle<int> r (getLocalBounds().reduced (4));
    textBox.setBounds (r);
}

bool AudioAnalyzer::getflag()
{
    return flag;
}

void AudioAnalyzer::clear()
{
    zeromem (samples, sizeof (samples));
    zeromem (saveBuf1, sizeof (saveBuf1)); // ensure the saveBuf is not full of junk, on the first iteration of
                                            //pushing the buf to featureController
    zeromem (saveBuf2, sizeof (saveBuf2));
    accumulator = 0;
    subSample = 0;
    iteration = 0;
    counterBuf = 0;
    flag = false;
    //SAMPLE** featVal;
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
                                
                //for RMS calc only (ELSKA)
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
    
    counterSave = iteration % (numChannels*100);
    if(counterSave == 0 && iteration > 0){ //iteration > 0, to ensure that that we start saving into saveBuf1
        counterBuf++;
    }

    bufSelect = counterBuf % 2;
    
    //save to the buffers here
    if(bufSelect == 0){
    for (int chan = 0; chan < numChannels; ++chan){
        saveBuf1[counterSave + chan] = inputSave[chan];
        }
    }
    else{
        for (int chan = 0; chan < numChannels; ++chan){
            saveBuf2[counterSave + chan] = inputSave[chan];
        }
    }
    
    if(counterSave == 0 && bufSelect == 0){
        flag = true;
        std::cout << "flag1!" << flag;
        
        //TO DO: pass the save buff to feature extraction. it will be of size saveBuf[numChannels * 100 * 1024] (i think ?)//
        //but for now
        //std::cout << saveBuf1 << saveBuf1[2] << std::endl << iteration << std::endl;
        //AudioAnalyzer::pushSample is a void return function because all the FeatureFunction calls are pushed to animation within it, but
        // RMS = featureControler::CalcRMS(saveBuf); RMS will be the value passed to the animation, but the buffer in the    function will save exterior to this function::pushSample
        //FFT = featureControler::CalcFFT(saveBuf);
        //NOTE: as stated above OUR FEATURE:Extraction RETURNS MUST SAVE TO A GLOBAL VARIABLE THAT WILL BE ACCESSED BY THE GRAPHICS RENDERING FUNCTION
        
        // featureControllerObject = new FeatureController( INFO );
        // featVal = featureControlObject.getFeature(RMS);
     
        //set saveBuf to zero
        for(int i = 0; i < (numChannels*100*1024); ++i){
            saveBuf1[i] = 0;
        }
    }
    else if(counterSave == 0 && bufSelect == 1){
        flag = false;
        std::cout << "flag2!" << flag;
        
        for(int i = 0; i < (numChannels*100*1024); ++i){
            saveBuf2[i] = 0;
        }
    }        // end of save to buffer
        
    for(int i = 0; i < numChannels; i++) {
        iteration++; //ensures proper indexing of saveBuf, necessitates modulo numChannels*100 because it is counting (numChannels times) as fast.
    }
    
    
    //push to animation _ _ _ _ _ _ _ _ _ _ need to add different variables for different animation executions
    
    accumulator += newSample; //
    
    if (subSample == 0)
    {
        const int inputSamplesPerPixel = numChannels*100;
        
        samples[nextSample] = accumulator / inputSamplesPerPixel;
        nextSample = (nextSample + 1) % numElementsInArray (samples);
        subSample = inputSamplesPerPixel;
        accumulator = 0;
    }
    else
    {
        --subSample;
        
    }
}