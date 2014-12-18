//
// FeatureController.h
//
// =================================================================== //
//
// Citygram controller class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/8/14
// C Programming, Fall 2014
//
// =================================================================== //

#ifndef __CFEL__FeatureController__
#define __CFEL__FeatureController__

#include <stdio.h>
#include <math.h>

#include "FeatureExtraction.h"
#include "FeatureStatistics.h"

#include "FeatureClasses\FeatureRMS.h"

class FeatureController {
	private:
		// output parameters
		//FeatureExtraction*	m_feature;		// ***CHANGE TO ARRAY OF FEATURES?
		FeatureExtraction*	m_featureRMS;
		//FeatureStatistics	m_featureStatObject;
		
		// input parameters from JUCE
		SAMPLE*				m_buffer;
		int					m_bufSize;
		int					m_fs;
		int					m_winSize;
		int					m_hopSize;
	
	public:
		FeatureController(SAMPLE* buffer, int bufSize, int fs, int winSize, int hopSize);
		~FeatureController();

		void setFeature();	// create new Feature
		FeatureRMS* getRMSFeature();
		void exportFeatureData(); // xml
			
};

#endif