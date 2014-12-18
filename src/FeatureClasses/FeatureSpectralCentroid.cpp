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

#include "FeatureSpectralCentroid.h"

SAMPLE** FeatureSpectralCentroid::calculate_feature(){ // compute Spectral centroid

	double fSum = 0.0;
	double fWeightedSum = 0.0;
	
	SAMPLE fBinSize = this->get_fBinSize();
	
	/*for (int i = 0; i < this->get_winSize()/2; i++) { // column..frequency axis
		fWeightedSum += i*fBinSize*m_magSpec[i];
		fSum += pMagSpec[i];
	}

	if (fSum == 0.0)
		return 0.0;

	return fWeightedSum / fSum;*/

	// TODO: REMOVE (TEMPORARY HARD CODE TO TEST DEPENDENCIES)
	this->new_feature(5, 5);
	SAMPLE** feature = this->get_feature();

	return feature;
	
}