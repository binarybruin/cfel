//
// FeatureRMS.cpp
//
// =================================================================== //
//
// Citygram FeatureRMS class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/11/14
// C Programming, Fall 2014
//
// =================================================================== //

#include "FeatureRMS.h"

#include <iostream>
#include <fstream>

void FeatureRMS::set_rows_cols() {
	int bufSize = this->get_bufSize();
	int hopSize = this->get_hopSize();

	this->set_nCols(1);
	this->set_nRows(ceil(bufSize / (double)hopSize));
}

SAMPLE** FeatureRMS::calculate_feature(){
			int bufSize = this->get_bufSize();
			int hopSize = this->get_hopSize();
			int winSize = this->get_winSize();
			SAMPLE* buffer = this->get_signal();
			
			// set nCols and nRows (move to somewhere else?)
			//set_nCols(1);
			//set_nRows(ceil(bufSize/(double)hopSize));
			int nCols = get_nCols();
			int nRows = get_nRows();
			
			// allocate memory for feature
			this->new_feature(nRows, nCols);
			SAMPLE** feature = this->get_feature();
			
			// RMS calculation
			SAMPLE sqrSum;
			SAMPLE val;
			for (int i = 0; i < nCols; ++i){			
				for (int j = 0; j < nRows; ++j){
					sqrSum = 0.0;
					for (int k = 0; k < winSize; ++k){
						if (j*hopSize+k >= bufSize){ // conceptually zero-padding
							val = 0;
						}
						else{
							val = buffer[j*hopSize+k];
						}
						sqrSum += val*val;
					}
					feature[j][i] = sqrt(sqrSum/(SAMPLE)winSize);
				}
			}
			return feature;
		}
