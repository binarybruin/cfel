//
// FeatureSpectralPeak.h
//
// =================================================================== //
//
// Citygram feature class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/16/14
// C Programming, Fall 2014
//
// =================================================================== //

#ifndef __CFEL__FeatureController__
#define __CFEL__FeatureController__

#include <stdio.h>
#include <math.h>
#include <vector>

#include "../FeatureExtractionSpectral.h"
#include "../Utils/EuclidDist.h"

class FeatureSpectralFlux: public FeatureExtraction {

public:
	
	void calculate_feature();

};

#endif