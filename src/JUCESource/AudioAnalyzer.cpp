//
//  AudioAnalyzer.cpp
//  JuceProject
//
//  Michelle Auyoung, Jordan Juras, Jaeseong You

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
    float sumRMS = 0.0f;
    float sumZCR = 0.0f;
    for (int i = 0; i < 1024; i++){
        sumRMS += samplesRMS[i];
        sumZCR += samplesZCR[i];
    }
    
    String strRMS = String(sumRMS);
    String strZCR = String(sumZCR);
    
    g.fillAll (Colours::black);
    
    textBox.moveCaretToEnd();
    textBox.insertTextAtCaret ("RMS:" + strRMS + "                              " + "ZCR:" + strZCR + newLine);
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
    zeromem (samplesRMS, sizeof (samplesRMS));
    zeromem (samplesZCR, sizeof (samplesZCR));
    zeromem (saveBuf1, sizeof (saveBuf1)); // ensure the saveBuf is not full of junk, on the first iteration of
                                           //pushing the buf to featureController
    zeromem (saveBuf2, sizeof (saveBuf2));
    accumulatorRMS = 0;
    accumulatorZCR = 0;
    subSample = 0;
    iteration = 0;
    counterBuf = 0;
    flag = false;
    typedef float SAMPLE;
    bufSize = 2 * 100 * 1024;
    winSize = bufSize/60;
    hopSize = winSize/2;
    nCols = 1;
    nRows = ceil(bufSize/hopSize);
    
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



void AudioAnalyzer::pushSample (const float newSample, double (&inputSave)[2], int numChannels)
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
        std::cout << "Buffer1::" << std::endl;
        
        // parameter initialization:
        SAMPLE m_featureRMS[nCols][nRows];
        SAMPLE *buffer = saveBuf1;
        
        // RMS calculation
        SAMPLE sqrSum;
        SAMPLE val;
        for (int i = 0; i < nCols; ++i){
            for (int j = 0; j < nRows; ++j){
                sqrSum = 0.0;
                for (int k = 0; k < winSize; ++k){
                    if (j*hopSize+k >= bufSize){ // conceptually zero-padding
                        val = 0;
                    }
                    else{
                        val = buffer[j*hopSize+k];
                    }
                    sqrSum += val*val;
                }
                m_featureRMS[i][j] = sqrt(sqrSum/winSize);
            }
        }
        
        //ZERO CROSSING RATE
        
        SAMPLE m_featureZCR[nCols][nRows];
        int zcc; // zero crossing count
        for (int i = 0; i < nCols; ++i){
            for (int j = 0; j < nRows; ++j){
                zcc = 0;
                for (int k = 0; k < winSize; ++k){
                    if (j*hopSize+k+1 < bufSize){ // conceptually zero-padding
                        // check the sign of two consecutive samples
                        if (buffer[j*hopSize+k] < 0 && buffer[j*hopSize+k+1] > 0){
                            ++zcc;
                        }
                        if (buffer[j*hopSize+k] > 0 && buffer[j*hopSize+k+1] < 0){
                            ++zcc;
                        }
                    }
                }
                m_featureZCR[i][j] = (SAMPLE)zcc/winSize;
            }
        }

        sampleRMS = m_featureRMS[0][0];
        sampleZCR = m_featureZCR[0][0];
        std::cout << "RMS" << sampleRMS  << std::endl;
        std::cout << "ZCR" << sampleZCR  << std::endl;
        
        //set saveBuf to zero
        zeromem (saveBuf1, sizeof (saveBuf1));
        //for(int i = 0; i < (numChannels*100*1024); ++i){
         //   saveBuf1[i] = 0;
       // }
    }
    else if(counterSave == 0 && bufSelect == 1){
        flag = false;
        std::cout << "Buffer2::" << std::endl;
        
        // parameter initialization:
        SAMPLE m_featureRMS[nCols][nRows];
        SAMPLE *buffer = saveBuf2;
        
        // RMS calculation
        SAMPLE sqrSum;
        SAMPLE val;
        for (int i = 0; i < nCols; ++i){
            for (int j = 0; j < nRows; ++j){
                sqrSum = 0.0;
                for (int k = 0; k < winSize; ++k){
                    if (j*hopSize+k >= bufSize){ // conceptually zero-padding
                        val = 0;
                    }
                    else{
                        val = buffer[j*hopSize+k];
                    }
                    sqrSum += val*val;
                }
                m_featureRMS[i][j] = sqrt(sqrSum/winSize);
            }
        }
        
        //ZERO CROSSING RATE
        
        SAMPLE m_featureZCR[nCols][nRows];
        int zcc; // zero crossing count
        for (int i = 0; i < nCols; ++i){
            for (int j = 0; j < nRows; ++j){
                zcc = 0;
                for (int k = 0; k < winSize; ++k){
                    if (j*hopSize+k+1 < bufSize){ // conceptually zero-padding
                        // check the sign of two consecutive samples
                        if (buffer[j*hopSize+k] < 0 && buffer[j*hopSize+k+1] > 0){
                            ++zcc;
                        }
                        if (buffer[j*hopSize+k] > 0 && buffer[j*hopSize+k+1] < 0){
                            ++zcc;
                        }
                    }
                }
                m_featureZCR[i][j] = (SAMPLE)zcc/winSize;
            }
        }
        
        sampleRMS = m_featureRMS[0][0];
        sampleZCR = m_featureZCR[0][0];
        
        std::cout << "RMS" << sampleRMS  << std::endl;
        std::cout << "ZCR" << sampleZCR  << std::endl;
        
        zeromem (saveBuf2, sizeof (saveBuf2)); //clear saveBuf2
        
    }

    for(int i = 0; i < numChannels; i++) {
        iteration++; //ensures proper indexing of saveBuf, necessitates modulo numChannels*100 because it is counting (numChannels times) as fast.
    }
    
    
    //push to animation
    
    accumulatorRMS += sampleRMS;
    accumulatorZCR += sampleZCR;
    
    if (subSample == 0) //each time the saveBuf switches
    {
        const int inputSamplesPerPixel = numChannels*100;
        
        samplesRMS[nextSampleRMS] = accumulatorRMS / inputSamplesPerPixel;
        samplesZCR[nextSampleZCR] = accumulatorZCR / inputSamplesPerPixel;
        nextSampleRMS = (nextSampleRMS + 1) % numElementsInArray (samplesRMS);
        nextSampleZCR = (nextSampleZCR + 1) % numElementsInArray (samplesZCR);
        subSample = inputSamplesPerPixel;
        accumulatorRMS = 0;
        accumulatorZCR = 0; 
    }
    else
    {
        --subSample;
        
    }
}