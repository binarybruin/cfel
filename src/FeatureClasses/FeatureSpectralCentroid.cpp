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

void calculate_feature(){ // compute Spectral centroid

	double fSum = 0.0;
	double fWeightedSum = 0.0;
	double window[m_winSize];
	
	
	
	
	
	for (int i = 0; i < m_winSize/2; i++) { // column..frequency axis
		fWeightedSum += i*fBinSize*m_magSpec[i];
		fSum += pMagSpec[i];
	}

	if (fSum == 0.0)
		return 0.0;

	return fWeightedSum / fSum;
	
}