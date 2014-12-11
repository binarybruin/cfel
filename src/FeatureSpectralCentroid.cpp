//
// FeatureSpectralCentroid.cpp
//
// =================================================================== //
//
// Citygram FeatureSpectralCentroid class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/11/14
// C Programming, Fall 2014
//
// =================================================================== //

void calculate_magSpec(){

	magSpec = (SAMPLE**)malloc(nWinSize*sizeof(SAMPLE*));
	
	for (int i = 0; i < nWinSize; ++i){
		magSpec[i] = (SAMPLE*)malloc(nRows*sizeof(SAMPLE*));
	}

	// get the magnitude spectrum of the complex fft result
	for (int i = 0; i < nNumSamples/2+1; i++)
		magSpec[i] = abs(fftOut[i]);

	return magSpec;
}

void calculate_feature(){

	// TODO1: needs to window signal
	
	
	// TODO2: needs to FFT each signal

	
	// TODO3: needs to convert FFT results to magSpec
	

	double fSum = 0.0;
	double fWeightedSum = 0.0;

	for (int i = 0; i < nSize; i++) {
		fWeightedSum += i*fBinSize*pMagSpec[i];
		fSum += pMagSpec[i];
	}

	if (fSum == 0.0)
		return 0.0;

	return fWeightedSum / fSum;
	
}