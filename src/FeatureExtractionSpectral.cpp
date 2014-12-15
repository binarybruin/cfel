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

	m_magSpec = (SAMPLE**)malloc(nWinSize*sizeof(SAMPLE*));
	
	for (int i = 0; i < nWinSize; ++i){
		magSpec[i] = (SAMPLE*)malloc(nRows*sizeof(SAMPLE*));
	}

	// get the magnitude spectrum of the complex fft result
	for (int i = 0; i < nNumSamples/2+1; i++)
		magSpec[i] = abs(fftOut[i]);

}

