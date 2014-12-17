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

#include "FeatureZCR.h"

#include <iostream>
#include <fstream>

using namespace FeatureExtraction::Utils;

void FeatureZCR::calculate_feature(){
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
			m_feature = (SAMPLE**)malloc(nRows*sizeof(SAMPLE));
			for (int i = 0; i < nRows; ++i){
				m_feature[i] = (SAMPLE*)malloc(nCols*sizeof(SAMPLE*));
			}
			
			// ZCR calculation
			int zcc; // zero crossing count
			for (int i = 0; i < nCols; ++i){			
				for (int j = 0; j < nRows; ++j){
					zcc = 0;
					for (int k = 0; k < winSize; ++k){
						if (j*hopSize+k+1 < bufSize){ // conceptually zero-padding
							// check the sign of two consecutive samples
							if (buffer[j*hopSize+k] < 0 && buffer[j*hopSize+k+1] > 0){
								++zcc;
							}
							if (buffer[j*hopSize+k] > 0 && buffer[j*hopSize+k+1] < 0){
								++zcc;
							}
						}
					}
					m_feature[j][i] = (SAMPLE)zcc/winSize;
				}
			}	 
		}