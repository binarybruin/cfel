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

SAMPLE** FeatureSpectralFlux::calculate_feature(){

	SAMPLE* signal = this->get_signal();
	int sig_length = this->get_bufSize();
	int winSize = this->get_winSize();
	
	// set and get nCols and nRows
	set_nCols(1);
	int bufSize = this->get_bufSize();
	int hopSize = this->get_hopSize();
	set_nRows(ceil(bufSize/(double)hopSize));
	int nCols = get_nCols();
	int nRows = get_nRows();
	
	//memory allocation for feature
	this->new_feature(nRows, nCols);
	SAMPLE** feature = this->get_feature();
	
	// check input spectrum is same size as last spectrum
	/*static vector<SAMPLE> past;

	if (past.size() != sig_length) {
		if (past.size() == 0) {
			past.resize(sig_length, 0.0);
		}
		else {
			// TODO: Should throw error here
			return feature;
		}
	}

	// get magnitude spectrum
	SAMPLE** pMagSpec = this->get_magSpec();

	// calculate spectral flux of magnitude spectrum
	vector<SAMPLE> specFlux(nRows);

	for (int i = 0; i < nRows; i++)
		//specFlux[i] = fabs(pMagSpec[i] - past[i]);		// TODO: WHERE IS PAST INITIALIZED?

	past.assign(pMagSpec, pMagSpec + sig_length);

	//return EuclidDist::euclidDist(&specFlux[0], nSize);

	//this->set_signal(EuclidDist::euclidDist(&specFlux[0], sig_length));		// TODO: SAMPLE INCOMPATIBLE WITH TYPE FLOAT?*/

	return feature;
}