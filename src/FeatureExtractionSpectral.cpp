//
// FeatureExtractionSpectral.cpp
//
// =================================================================== //
//
// Citygram FeatureSpectralSpectral class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/12/14
// C Programming, Fall 2014
//
// =================================================================== //

#include "FeatureExtractionSpectral.h"

FeatureExtractionSpectral::FeatureExtractionSpectral(){
}

FeatureExtractionSpectral::~FeatureExtractionSpectral(){
}


int FeatureExtractionSpectral::get_winType(){
	return m_winType; // refer to WindowFunction.h for detailed info on Windows
}

void FeatureExtractionSpectral::set_winType(int winType){
	m_winType = winType;
}
		
SAMPLE** FeatureExtractionSpectral::get_magSpec(){
	return m_magSpec;
}
		
void FeatureExtractionSpectral::calculate_magSpec(){
	int hopSize = this->get_hopSize();
	int winSize = this->get_winSize();
	int nRows = this->get_nRows(); // vertical time axis
	
	// memory allocation for m_magSpec;
	m_magSpec = (SAMPLE**) malloc (winSize*sizeof(SAMPLE*));
	for (int i = 0; i < winSize / 2 + 1; ++i){
		m_magSpec[i] = (SAMPLE*)malloc(nRows*sizeof(SAMPLE*));
	}
	
	// get buffer
	SAMPLE* buffer = this->get_buffer();
	
	// get window
	WindowFunction* windowObj = new WindowFunction(winSize);
	SAMPLE* window = windowObj->getWindow();
	SAMPLE winSig[winSize]; // windowed sig
	
	// get the magnitude spectrum
	SAMPLE* fftOut; 
	for (i = 0; i < nRows; ++i){
		// hopping (happens in buffer) and windowing
		for (int j = 0; j < winSize; ++j){
			winSig[j] = buffer[i*hopSize+j]*window[j];
			
		}
		fftout = FFT(winSig);
		
		for (j = 0; j < winSize/2+1; ++j){
			m_magSpec[i][j] = (SAMPLE)abs(fftOut[i]);
		}
	}
}

