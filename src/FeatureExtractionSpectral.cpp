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

FeatureExtractionSpectral::FeatureExtractionSpectral(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize, WindowType winType){
	set_signal(signal);
	set_bufSize(bufSize);
	set_fs(fs);
	set_winSize(winSize);
	set_hopSize(hopSize);
	set_winType(winType);
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


WindowType FeatureExtractionSpectral::get_winType(){
	return m_winType; // refer to WindowFunction.h for detailed info on Windows
}

void FeatureExtractionSpectral::set_winType(WindowType winType){
	this->m_winType = winType;
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
	// bring in necessary variables
	SAMPLE* signal = this->get_signal();
	int bufSize = this->get_bufSize();
	int hopSize = this->get_hopSize();
	int winSize = this->get_winSize();
	WindowType winType = this->get_winType();
	
	// TODO: set row elsewhere?
	set_nRows(ceil(bufSize/(double)hopSize)); 
	int nRows = this->get_nRows();

	int nFFTCols = (winSize / 2) + 1;
	
	// get window; TODO: get this elsewhere?
	SAMPLE* window; // Q: const value?
	WindowFunction* winObj = new WindowFunction(winSize, winType);
	window = winObj->get_window();
	
	// memory allocation for m_magSpec (vertical time axis and horizontal window)
	this->m_magSpec = (SAMPLE**)malloc(nFFTCols*sizeof(SAMPLE*));
	for (int i = 0; i < nFFTCols; ++i){
		m_magSpec[i] = (SAMPLE*)malloc(nRows * sizeof(SAMPLE));
	}
	
	std::vector<std::complex<double> > complexIn(winSize);
	std::vector<std::complex<double> > fftOut;
	
	// store double array as complex data type to conform with the FFT algorithm used here
	for (int i = 0; i < nRows; i++){
		for (int j = 0; j < winSize; j++){
			if (i*hopSize + j < bufSize){
				complexIn[j] = std::complex<SAMPLE>(signal[i*hopSize + j] * window[j], 0.0);
			}
			else{ //zero-padding
				complexIn[j] = std::complex<SAMPLE>(0 * window[j], 0.0);
			}
		}
		fftOut = FFT::fft(complexIn);
		for (int j = 0; j < nFFTCols; j++){
			m_magSpec[i][j] = abs(fftOut[i]);
		}
	}
}

