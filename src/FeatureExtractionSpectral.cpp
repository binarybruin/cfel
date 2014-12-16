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

	int winSize = this->get_winSize();

	m_magSpec = (SAMPLE**) malloc (winSize*sizeof(SAMPLE*));
	
	for (int i = 0; i < winSize; ++i){
		m_magSpec[i] = (SAMPLE*)malloc(this->get_nRows()*sizeof(SAMPLE*));
	}

	// get window
	WindowFunction* windowObj = new WindowFunction(winSize);
	SAMPLE* window = windowObj->getWindow();		// TODO: Where do you use window? - added fft, but not sure how to use here
	
	// get fft
	SAMPLE* fftOut = fft(window);
	
	// get the magnitude spectrum of the complex fft result
	for (int i = 0; i < winSize / 2 + 1; i++)
		*m_magSpec[i] = (SAMPLE)abs(fftOut[i]);

}

