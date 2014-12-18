//
// FeatureRMS.h
//
// =================================================================== //
//
// Citygram feature class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/10/14
// C Programming, Fall 2014
//
// =================================================================== //

#include "../FeatureExtraction.h"

class FeatureRMS: public FeatureExtraction
{
	public:
		SAMPLE** calculate_feature();
};