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

FeatureExtractionSpectral::FeatureExtractionSpectral(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize){
	set_signal(signal);
	set_bufSize(bufSize);
	set_fs(fs);
	set_winSize(winSize);
	set_hopSize(hopSize);
	calculate_fBinSize();
	calculate_magSpec();
}

FeatureExtractionSpectral::~FeatureExtractionSpectral(){
	int winSize = this->get_winSize();
	int nCols = this->get_nCols();
	
	if (m_signal != NULL){
		free(m_signal);
	}
	
	if (m_feature != NULL){
		for (int i = 0; i < nCols; ++i){
			free(m_feature[i]);
		}
	}
	
	if (m_magSpec != NULL){
		for (int i = 0; i < winSize / 2 + 1; ++i){
			free(m_magSpec[i]);
		}
	}
}


int FeatureExtractionSpectral::get_winType(){
	return m_winType; // refer to WindowFunction.h for detailed info on Windows
}

void FeatureExtractionSpectral::set_winType(int winType){
	m_winType = winType;
}

SAMPLE FeatureExtractionSpectral::get_fBinSize(){
	return m_fBinSize;
}

void FeatureExtractionSpectral::calculate_fBinSize(){
	int fs = this->get_fs();
	int winSize = this->get_winSize();
	m_fBinSize = (fs/2)/winSize;
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
	
	// get buffer (signal)
	SAMPLE* signal = this->get_signal();
	
	// get window
	WindowFunction* windowObj = new WindowFunction(winSize);
	SAMPLE* window = windowObj->get_window();
	SAMPLE winSig[winSize]; // tODO: winSize must be constant??
	
	// get the magnitude spectrum
	SAMPLE* fftOut; 
	for (int i = 0; i < nRows; ++i){
	
		// hopping (happens in buffer) and windowing
		for (int j = 0; j < winSize; ++j){
			winSig[j] = signal[i*hopSize+j]*window[j];
			
		}
		
		fftOut = fft(winSig); // TODO: fft outcome not compatible with SAMPLE
		
		// put the fftout to m_magSpec
		for (int j = 0; j < winSize / 2 + 1; ++j){
			m_magSpec[i][j] = (SAMPLE)abs(fftOut[i]);
		}
	}
}

