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

using namespace FeatureRMS::Utils;

void FeatureRMS::calculate_feature(){
			int bufSize = this->get_bufSize();
			int hopSize = this->get_hopSize();
			int winSize = this->get_winSize();
			SAMPLE* buffer = this->get_signal();
			
			// set nCols and nRows (move to somewhere else?)
			set_nCols(1);
			set_nRows(ceil(bufSize/hopSize));
			int nCols = get_nCols();
			int nRows = get_nRows();
			
			// allocate memory for feature
			m_feature = (SAMPLE**)malloc(nCols*sizeof(SAMPLE*));
			for (int i = 0; i < nCols; ++i){
				m_feature[i] = (SAMPLE*)malloc(nRows*sizeof(SAMPLE*));
			}
			
			// RMS calculation
			SAMPLE sqrSum = 0.0;
			SAMPLE val;
			for (i = 0; i < nCols; ++i){			
				for (int j = 0; j < nRows; ++j){
					for (int k = 0; k < winSize; ++k){
						if (j*hopSize+k >= bufSize){ // conceptually zero-padding
							val = 0;
						}
						else{
							val = buffer[j*hopSize+k];
						}
						sqrSum += val*val;
					}
				}
				m_feature[j][i] = sqrt(sqrSum/(SAMPLE)winSize);
			}
		}
