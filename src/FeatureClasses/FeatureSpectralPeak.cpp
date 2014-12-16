//
// FeatureSpectralPeak.cpp
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

void FeatureSpectralPeak::calculate_feature(){

	
	int fs = this->get_fs();
	SAMPLE* signal = this->get_signal();
	int bufSize = this->get_bufSize();
	int winSize = this->get_winSize();
	int hopSize = this->get_hopSize();
	SAMPLE fBinSize = this->get_fBinSize();
	
	// set and get nCols and nRows
	set_nCols(1);
	set_nRows(ceil(bufSize/hopSize);
	nCols = get_nCols();
	nRows = get_nRows();
	
	// allocate memory for feature
	m_feature = (SAMPLE**)malloc(nCols*sizeof(SAMPLE*));
	for (int i = 0; i < nCols; ++i){
		m_feature[i] = (SAMPLE*)malloc(nRows*sizeof(SAMPLE*));
	}

	// get magnitude spectrum
	FeatureExtractionSpectral *spectral = new FeatureExtractionSpectral();
	SAMPLE** pMagSpec = spectral->get_magSpec();

	
	for (int i = 0; i < nRows; i++)
		// TODO: get the frequency bin size and multiply with the INDEX of the frequeny bin of the largest value
		m_feature[i] = std::max_element("entireRow")*fBinSize; // TODO: need to be fixed

}