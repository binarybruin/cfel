FeatureRMS::calculate_feature(){
			
			// set nCols and nRows
			nCols = 1;
			nRows = ceil(bufSize/hopSize);
			
			// allocate memory for feature
			feautre = (SAMPLE**)malloc(nCols*sizeof(SAMPLE*));
			for (int i = 0; i < nCols; i++){
				feature[i] = (SAMPLE*)calloc(nRows*sizeof(SAMPLE*));
			}
			
			// RMS calculation
			if (winSize == 0){ 
				return 0.0;
			}
			else if (winSize > bufSize){
				printf("winSize exceeds bufSize\n");
				return 1.0;
			}
			else{
				SAMPLE squareSum = 0.0
				for (i = 0; i < nRows; i += hopSize){ // a hop
					SAMPLE squareSum = 0.0;
			
					for (int j = 0; j < winSize; j++){ // sum values within window
						if (i*winSize+j >= bufSize){ // conceptual zero-padding
							break;
						}
						squareSum += signal[i*winSize+j] * signal[i*winSize+j];
					}
					feature[i][nCols] = sqrt(squareSum / (SAMPLE)winSize);
				}
			}
			return feature; 
		}