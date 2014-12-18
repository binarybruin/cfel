//
// FeatureController.cpp
//
// =================================================================== //
//
// Citygram controller class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/11/14
// C Programming, Fall 2014
//
// =================================================================== //

#include "FeatureController.h"

#include <iostream>
#include <fstream>

// constructor/deconstructor
FeatureController::FeatureController(SAMPLE* buffer, int bufSize, int fs, int winSize, int hopSize) {

	m_buffer = (SAMPLE*)malloc(sizeof(SAMPLE) * bufSize);
	memcpy(m_buffer, buffer, bufSize);
	m_bufSize = bufSize;
	m_fs = fs;
	m_winSize = winSize;
	m_hopSize = hopSize;
}

void FeatureController::setFeature(){
	
	m_featureRMS = new FeatureRMS::FeatureExtraction(m_buffer, m_bufSize, m_fs, m_winSize, m_hopSize);

}

FeatureRMS* FeatureController::getRMSFeature() {

	return (FeatureRMS*)m_featureRMS;

}

void FeatureController::exportFeatureData() {

	// TODO: 

}