void FeatureZCR::calculate_feature(){
			
			// set nCols and nRows (move to somewhere else?)
			n_nCols = 1;
			m_nRows = ceil(m_bufSize/m_hopSize);
			
			// allocate memory for feature
			m_feautre = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*));
			for (int i = 0; i < m_nCols; ++i){
				m_feature[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE*));
			}
			
			// ZCR calculation
			if (m_winSize <= 0){ 
				printf("Check your winSize.\n");
				EXIT(1);
			}
			else if (m_winSize > m_bufSize){
				printf("winSize exceeds bufSize.\n");
				EXIT(1);
			}
			else{
			int zcc; // zero crossing count
				for (i = 0; i < m_nCols; ++i){			
					for (int j = 0; j < m_nRows; ++j){
						zcc = 0;
						for (int k = 0; k < m_winSize; ++k){
							if (j*m_hopSize+k <= m_nCols){
								// check the sign of two consecutive samples
								if (m_signal[j*m_hopSize+k] < 0 && m_signal[j*m_hopSize+k+1] > 0){
									++zcc;
								}
								if (m_signal[j*m_hopSize+k] > 0 && m_signal[j*m_hopSize+k+1] < 0){
									++zcc;
								}
							}
						}
						m_feature[j][i] = (SAMPLE)zcc/m_winSize;
					}
				}	 
			}
		}