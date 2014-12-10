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
#include "FeatureSystem.h"

class FeatureController {
	private:
		FeatureSystem		m_sysInfo;		// get system information

		FeatureExtraction	m_feature;		// CHANGE TO ARRAY OF FEATURES?
		//FeatureRMS	m_rms;
		//FeatureZCR	m_zcr;
		//FeatureMFCC	m_mfcc;

		SAMPLE*				m_buffer;
		SAMPLE*				m_reader;		// pointer to read buffer
		SAMPLE*				m_writer;		// pointer to write buffer

	public:
		FeatureController(FeatureSystem systemObj);

		FeatureExtraction	setFeature();	// create new Feature

		SAMPLE*				get_inputAudio();
		void				write_audio(float* buffer, float* readPointer, float* writePointer);

		void				visualize(float* buffer);
};

#endif