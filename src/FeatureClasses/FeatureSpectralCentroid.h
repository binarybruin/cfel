//
// FeatureSpectralCentroid.h
//
// =================================================================== //
//
// Citygram feature class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/11/14
// C Programming, Fall 2014
//
// =================================================================== //

#include "../FeatureExtraction.h"
#include "../FeatureExtractionSpectral.h"

class FeatureSpectralCentroid: public FeatureExtractionSpectral
{
	public:
		SAMPLE** calculate_feature();
};


