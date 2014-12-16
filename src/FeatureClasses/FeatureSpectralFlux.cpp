//
// FeatureSpectralFlux.cpp
//
// =================================================================== //
//
// Citygram feature class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/15/14
// C Programming, Fall 2014
//
// =================================================================== //

#include "FeatureSpectralFlux.h"

#include <iostream>
#include <fstream>

using namespace FeatureExtraction::Utils;

void FeatureSpectralFlux::calculate_feature(){

	SAMPLE* signal = this->get_signal();
	int sig_length = this->get_bufSize();
	int winSize = this->get_winSize();
	
	// set and get nCols and nRows
	set_nCols(1);
	set_nRows(ceil(bufSize/hopSize);
	nCols = get_nCols();
	nRows = get_nRows();
	
	//memory allocation for feature
	m_feature = (SAMPLE**)malloc(nCols*sizeof(SAMPLE*));
	for (int i = 0; i < nCols; ++i){
		m_feature[i] = (SAMPLE*)malloc(nRows*sizeof(SAMPLE*));
	}
	
	// check input spectrum is same size as last spectrum
	static vector<SAMPLE> past;

	if (past.size() != sig_length) {
		if (past.size() == 0) {
			past.resize(sig_length, 0.0);
		}
		else {
			// TODO: Should throw error here
			return;
		}
	}

	// get magnitude spectrum
	FeatureExtractionSpectral *spectral = new FeatureExtractionSpectral();		// TODO: BUT WHERE DOES THIS GET INITIALIZED? --> in constructor
	SAMPLE** pMagSpec = spectral->get_magSpec();

	// calculate spectral flux of magnitude spectrum
	vector<SAMPLE> specFlux(nRows);

	for (int i = 0; i < nRows; i++)
		specFlux[i] = fabs(pMagSpec[i] - past[i]);		// TODO: WHERE IS PAST INITIALIZED?

	past.assign(pMagSpec, pMagSpec + sig_length);

	//return EuclidDist::euclidDist(&specFlux[0], nSize);

	this->set_signal(EuclidDist::euclidDist(&specFlux[0], sig_length));		// TODO: SAMPLE INCOMPATIBLE WITH TYPE FLOAT?
}