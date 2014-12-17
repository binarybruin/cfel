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
#include <alogrithm>

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
	set_nRows(ceil(bufSize / hopSize);
	int nCols = get_nCols();
	int nRows = get_nRows();

	// allocate memory for feature
	this->m_feature = (SAMPLE**)malloc(nCols*sizeof(SAMPLE*));
	for (int i = 0; i < nCols; ++i){
		m_feature[i] = (SAMPLE*)malloc(nRows*sizeof(SAMPLE*));
	}

	// get magnitude spectrum
	SAMPLE** magSpec = this->get_magSpec();
	SAMPLE* oneRow;
	int maxIdx;
	for (int i = 0; i < nRows; i++){
		// take one entire row and its value
		oneRow = m_feature[i];
		int rowLen = sizeof(oneRow)/ sizeof(SAMPLE);
		SAMPLE maxVal = *std::max_element(oneRow, oneRow + rowLen);

		// compute the distance
		maxIdx = *std::distance(oneRow, maxVal);
		
		// get the freq value
		m_feature[i][0] = maxIdx*fBinSize;
	}
}