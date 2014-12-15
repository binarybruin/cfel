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
using namespace std;

// constructor/deconstructor
void FeatureController::setFeature(SAMPLE* buffer, int bufSize, int fs, int winSize, int hopSize){
	
	this->m_feature = new FeatureExtraction(buffer, bufSize, fs, winSize, hopSize);

}

SAMPLE** FeatureController::getFeature() {

	return this->m_feature->get_feature();

}

void FeatureController::exportFeatureData() {

	// TODO: 

}