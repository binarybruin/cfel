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

FeatureExtractionSpectral::FeatureExtractionSpectral(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize, WindowType winType)
{
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

	SAMPLE* signal = this->get_signal();
	SAMPLE** feature = this->get_feature();
	
	if (signal != NULL){
		free(signal);
	}
	
	if (feature != NULL){
		for (int i = 0; i < nCols; ++i){
			free(feature[i]);
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
	set_nRows((int)ceil(bufSize/(double)hopSize)); 
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

// getters and setters

SAMPLE* FeatureExtractionSpectral::get_signal(){
	if (this->m_signal == NULL){
		printf("m_signal is null\n");
		exit(1);
	}
	else{
		return this->m_signal;
	}
}

void FeatureExtractionSpectral::set_signal(SAMPLE* signal){
	if (signal == NULL){
		printf("input signal is null\n");
		return;
	}
	else{
		int bufSize = get_bufSize();
		this->m_signal = (SAMPLE*)malloc(sizeof(SAMPLE)*bufSize);
		this->m_signal = signal;
	}
}

int FeatureExtractionSpectral::get_bufSize(){
	return this->m_bufSize;
}

void FeatureExtractionSpectral::set_bufSize(int bufSize){
	this->m_bufSize = bufSize;
}

int FeatureExtractionSpectral::get_fs(){
	return this->m_fs;
}

void FeatureExtractionSpectral::set_fs(int fs){
	this->m_fs = fs;
}

int FeatureExtractionSpectral::get_winSize(){
	return this->m_winSize;
}

void FeatureExtractionSpectral::set_winSize(int winSize){
	this->m_winSize = winSize;
}

int FeatureExtractionSpectral::get_hopSize(){
	return this->m_hopSize;
}

void FeatureExtractionSpectral::set_hopSize(int hopSize){
	this->m_hopSize = hopSize;
}

// feature computation

int FeatureExtractionSpectral::get_nRows(){
	return this->m_nRows;
}

void FeatureExtractionSpectral::set_nRows(int nRows){
	this->m_nRows = nRows;
}

int FeatureExtractionSpectral::get_nCols(){
	return this->m_nCols;
}

void FeatureExtractionSpectral::set_nCols(int nCols){
	this->m_nCols = nCols;
}


SAMPLE** FeatureExtractionSpectral::get_feature(){
	return this->m_feature;
}

void FeatureExtractionSpectral::new_feature(int nRows, int nCols){
	m_feature = (SAMPLE**)malloc(nRows*sizeof(SAMPLE*));
	for (int i = 0; i < nCols; ++i){
		m_feature[i] = (SAMPLE*)malloc(nCols*sizeof(SAMPLE));
	}
}

SAMPLE** FeatureExtractionSpectral::calculate_feature(){
	return m_feature;
}

// preprocess

void FeatureExtractionSpectral::preprocess(){
	return;
}
