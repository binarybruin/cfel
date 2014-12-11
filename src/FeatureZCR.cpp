FeatureZCR:: void calculate_feature(){
			
			// set nCols and nRows (move to somewhere else?)
			n_nCols = 1;
			m_nRows = ceil(m_bufSize/m_hopSize);
			
			// allocate memory for feature
			feautre = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*));
			for (int i = 0; i < m_nCols; ++i){
				feature[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE*));
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
				 for (i = 0; i < m_nCols; ++i){			
					for (int j = 0; j < m_nRows; ++j){
						for (int k = 0; k < m_winSize; ++k){
							if (j*m_hopSize+k >= m_nCols){
								val = 0;
							}
							else{
							}

						}
					}
					feature[j][i] = ???;
				}
				 
				 
				}
			}
			return feature; 
		}