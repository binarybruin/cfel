FeatureRMS::calculate_feature(){
			nCols = ceil(bufSize/hopSize);
			nRows = 1;
			feautre = calloc(nCol*nRow*sizeof(SAMPLE));
		
			if (winSize == 0){ 
				return 0.0;
			}
			else if (winSize > bufSize){
				printf("Your winSize exceeds bufSize\n");
				return 1.0;
			}
			else{
				SAMPLE squareSum = 0.0
				for (int i = 0; i < nCol; i += hopSize){
					SAMPLE squareSum = 0.0;
			
					for (int j = 0; j < winSize; j++){
						if (i*winSize+j >= bufSize){ // conceptual zero-padding
							break;
						}
						squareSum += signal[i*winSize+j] * signal[i*winSize+j];
					}
					feature[i] = sqrt(squareSum / (SAMPLE)winSize);
				}
			}
			return feature; 
		}