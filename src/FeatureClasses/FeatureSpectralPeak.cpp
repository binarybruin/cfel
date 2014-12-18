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

#include "FeatureSpectralPeak.h"

#include <iostream>
#include <fstream>
#include <algorithm>

//using namespace FeatureExtraction::Utils;

SAMPLE** FeatureSpectralPeak::calculate_feature(){
	
	int fs = this->get_fs();
	SAMPLE* signal = this->get_signal();
	int bufSize = this->get_bufSize();
	int winSize = this->get_winSize();
	int hopSize = this->get_hopSize();
	SAMPLE fBinSize = this->get_fBinSize();

	// set and get nCols and nRows
	set_nCols(1);
	set_nRows(ceil(bufSize / hopSize));
	int nCols = get_nCols();
	int nRows = get_nRows();

	// allocate memory for feature
	this->new_feature(nRows, nCols);
	SAMPLE** feature = this->get_feature();

	// get magnitude spectrum
	SAMPLE** magSpec = this->get_magSpec();
	SAMPLE* oneRow;
	int maxIdx;
	for (int i = 0; i < nRows; i++){
		// take one entire row and its value
		oneRow = magSpec[i];
		int rowLen = sizeof(oneRow)/ sizeof(SAMPLE);
		SAMPLE maxVal = *std::max_element(oneRow, oneRow + rowLen);

		// compute the distance
		maxIdx = *std::distance(oneRow[0], maxVal);
		
		// get the freq value
		feature[i][0] = maxIdx*fBinSize;
	}

	return feature;
}