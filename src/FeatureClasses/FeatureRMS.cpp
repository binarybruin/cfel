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

void FeatureRMS::calculate_feature(){
			
			// set nCols and nRows (move to somewhere else?)
			n_nCols = 1;
			m_nRows = ceil(m_bufSize/m_hopSize);
			
			// allocate memory for feature
			m_feautre = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*));
			for (int i = 0; i < m_nCols; ++i){
				m_feature[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE*));
			}
			
			// RMS calculation
			if (m_winSize <= 0){ 
				printf("Check your winSize.\n");
				EXIT(1);
			}
			else if (m_winSize > m_bufSize){
				printf("winSize exceeds bufSize.\n");
				EXIT(1);
			}
			else{
				SAMPLE sqrSum = 0.0
				SAMPLE val;
				for (i = 0; i < m_nCols; ++i){			
					for (int j = 0; j < m_nRows; ++j){
						for (int k = 0; k < m_winSize; ++k){
							if (j*m_hopSize+k >= m_nCols){
								val = 0;
							}
							else{
								val = m_signal[j*m_hopSize+k];
							}
							sqrSum += val*val;
						}
					}
					m_feature[j][i] = sqrt(sqrSum/(SAMPLE)m_winSize);
				}
			}
		}