//
// FeatureStatistics.cpp
//
// =================================================================== //
//
// Citygram feature class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/10/14
// C Programming, Fall 2014
//
// =================================================================== //

#include "FeatureStatistics.h"

// constructor/deconstructor
FeatureStatistics(SAMPLE** feature, int nRows, int nCols, int sWinSize, int sHopSize){
	set_nRows(nRows); // order matters
	set_nCols(nCols);
	set_feature(feature);
	
	set_nStatCols(); // no input; computed from nCols
	set_nStatRows(); // no input; computed from nRows and sHopSize
	set_sWinSize(sWinSize);
	set_sHopSize(sHopSize);
	
	set_features();
	set_d1Features();
	set_d2Features();
}

~FeatureStatistics(){
	// free feature
	if (m_feature != NULL){
		for (int i = 0; i < nCols; ++i){
			free(m_feature[i]);
		}
		free(m_freature);
	}
	// free mean
	if (m_mean != NULL){
		for (i = 0; i < nStatCols; ++i){// 
			free(m_mean[i]); 
		}
		free(m_mean);
	}
	// free std
	if (m_std != NULL){
		for (i = 0; i < nStatCols; ++i){ //
			free(m_std[i]); 
		}
		free(m_std);
	}
	// free var
	if (m_var != NULL){
		for (i = 0; i < nStatCols; ++i){ //
			free(m_var[i]); 
		}
		free(m_var);
	}
	
	
	// free d1Feature
	if (m_d1Feature != NULL){
		for (i = 0; i < nCols; ++i){
			free(m_d1Feature[i]); 
		}
		free(m_d1Freature);
	}
	// free d1Mean
	if (m_d1Mean != NULL){
		for (i = 0; i < nStatCols; ++i){
			free(m_d1Mean[i]); 
		}
		free(m_d1Mean);
	}
	// free d1Std
	if (m_d1Std != NULL){
		for (i = 0; i < nStatCols; ++i){
			free(m_d1Std[i]); 
		}
		free(m_d1Std);
	}
	// free d1Var
	if (m_d1Var != NULL){
		for (i = 0; i < nStatCols; ++i){
			free(m_d1Var[i]); 
		}
		free(m_d1Var);
	}
	
	// free d2Feature
	if (m_d2Feature != NULL){
		for (i = 0; i < nCols; ++i){
			free(m_d2Feature[i]); 
		}
		free(m_d2Freature);
	}
	// free d2Mean
	if (m_d2Mean != NULL){
		for (i = 0; i < nStatCols; ++i){
			free(m_d2Mean[i]); 
		}
		free(m_d2Mean);
	}
	// free d2Std
	if (m_d2Std != NULL){
		for (i = 0; i < nStatCols; ++i){
			free(m_d2Std[i]); 
		}
		free(m_d2Std);
	}
	// free d2Var
	if (m_d2Var != NULL){
		for (i = 0; i < nStatCols; ++i){
			free(m_d2Var[i]); 
		}
		free(m_d2Var);
	}
}


SAMPLE** get_feature(){
	return m_feature;
}

void set_feature(SAMPLE** feature){
	// input check
	if (feature == NULL){
		EXIT(1);
	}
	
	// memory allocation 
	if (m_feature == NULL){ // is a pointer NULL by default when declared?
		m_feature  = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*));
		for (int i = 0; i < m_nCols; ++i){
			m_feature[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE));
		}
	}
	
	// set feature
	m_feature = feature;
}

int get_nRows(){
	return m_nRows
}

void set_nRows(int nRows){
	m_nRows = nRows;
}

int get_nCols(){
	return m_nCols;
}

void set_nCols(int nCols){
	m_nCols = nCols;
}

int get_nStatRows(){
	return m_nStatRows;
}

void set_nStatRows(){
	m_nStatRows =  ceil(m_nRows/m_nHopSize);
}

int get_nStatCols(){
	return m_nStatCols;
}

void set_nStatRows(){
	m_nStatCols = m_nCols;
}

int get_sWinSize(){
	return m_sWinSize;
}

void set_sWinSize(int sWinSize){
	m_sWinSize = sWinSize;
}

int get_sHopSize(){
	return m_sHopSize;
}

void set_sHopSize(int sHopSize){
	m_sHopSize = sHopSize;
}

//SAMPLE* get_featureTime();
// void set_featureTime()




SAMPLE** get_mean(){
	return m_mean;
}

SAMPLE** get_std(){
	return m_std;
}

SAMPLE** get_var(){
	return m_var;
}

void set_features(){
	// memory allocation
	m_mean = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
		m_mean[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_var = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; ++i){
		m_var[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_std = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; ++i){
		m_std[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	
	// calculate feature variables
	m_mean = calcualte_mean(m_feature);
	m_var = calculate_var(m_feature, m_mean);
	m_std =calculate_var2std(m_var);
}




SAMPLE** get_d1Feature(){
	return m_d1Feature;
}

SAMPLE** get_d1Mean(){
	return m_d1Mean;
}

SAMPLE** get_d1Std(){
	return m_d1Std;
}

SAMPLE** get_d1Var(){
	return m_d1Var;
}

void set_d1Features(){
	// memory allocation
	m_d1Feature = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nCols; ++i){
		m_d1Feature[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE));
	}
	m_d1Mean = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; ++i){
		m_d1Mean[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_d1Var = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; ++i){
		m_d1Var[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_d1Std = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; ++i){
		m_d1Std[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	
	// calculate d1 feature variables
	m_d1Feature = calculate_delta(m_feature);
	m_d1Mean = calcualte_mean(m_d1Feature);
	m_d1Var = calculate_var(m_d1Feature, m_d1Mean);
	m_d1Std = calculate_var2std(m_d1Var);
}

SAMPLE** get_d2Feature(){
	return m_d2Feature;
}

SAMPLE** get_d2Mean(){
	return m_d2Mean; 
}

SAMPLE** get_d2Std(){
	return m_d2Std;
}

SAMPLE** get_d2Var(){
	return m_d2Var;
}

void set_d2Features(){
	// memory allocation
	m_d2Feature = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nCols; ++i){
		m_d2Feature[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE));
	}
	m_d2Mean = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; ++i){
		m_d2Mean[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_d2Var = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; ++i){
		m_d2Var[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_d2Std = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; ++i){
		m_d2Std[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	
	// calculate
	m_d2Feature = calculate_delta(m_d1Feature);
	m_d2Mean = calcualte_mean(m_d2Feature);
	m_d2Var = calculate_var(m_d2Feature, m_d2Mean);
	m_d2Std = calculate_var2std(m_d2Var);
}


SAMPLE** calculate_mean(SAMPLE** feature){
	// input check
	if (feature == NULL){
		printf("input is NULL");
		EXIT(1);
	}
	
	// memory allocation
	SAMPLE** retVal  = (SAMPLE**)malloc(nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < nStatCols; ++i){
        retVal[i] = (SAMPLE*)malloc(nStatRows*sizeof(SAMPLE));
    }
	
	//take column by column to compute mean within each hopping window	
	SAMPLE sum;
	SAMPLE val;
	for (i = 0; i < m_nStatCols; ++i){
		for (int j = 0; j < m_nStatRows; ++j){
		    sum = 0;
			for (int k = 0; k < m_sWinSIze; ++k){
			    if (j*m_sHopSize+k >= m_nRows){ 
					val = 0;
                }
				else{
					val = feature[j*m_sHopSize+k][i];
				}
                sum += val;
            }
            retVal[j][i] = sum/m_sWinSIze;
        }
    }
    return retVal;
}


SAMPLE** calculate_var(SAMPLE** feature, SAMPLE** mean){
	// input check
	if (feature == NULL | mean == NULL){
		printf("input is NULL");
		EXIT(1);
	}
	
	// memory allocation
	SAMPLE** retVal  = (SAMPLE**)malloc(nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < nStatCols; ++i){
        retVal[i] = (SAMPLE*)malloc(nStatRows*sizeof(SAMPLE));
    }
	
	// variance calculation
	SAMPLE sqrSum;
	SAMPLE dif;
	SAMPLE val;
	for (i = 0; i < m_nStatCols; ++i){
		for (int j = 0; j < m_nStatRows; ++j){
		    sum = 0;
			for (int k = 0; k < m_sWinSIze; ++k){
			    if (j*m_sHopSize+k >= m_nRows){ // zero-padding
                    val = 0;
                }
				else{
					val = feature[j*m_sHopSize+k][i];
				}
                dif = val-mean[j][i];
				sqrSum += dif*dif;
            }
            retVal[j][i] = sqrSum/(m_sWinSIze-1);
        }
    }
    return retVal;
}


SAMPLE** calculate_var2std(SAMPLE** var){
	// input check
	if (var == NULL){
		printf("input is NULL");
		EXIT(1);
	}

	// memory allocation
	SAMPLE** retVal  = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
        retVal[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
    }
	
	// std calculation
	for (i = 0; i < m_nStatCols; ++i){
		for (int j = 0; j < m_nStatRows; ++j){
		    retVal[j][i] = sqrt(var[j][i]);
        }
    }
    return retVal;
}


SAMPLE** calculate_delta(SAMPLE** feature){
	// input check
	if (feature == NULL){
		printf("input is NULL");
		EXIT(1);
	}

	// memory allocation
	SAMPLE** retVal  = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
        retVal[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE));
    }
	
	// difference calculation
	SAMPLE curr;
	SAMPLE next;
	for (i = 0; i < m_nCols; ++i){
		for (int j = 0; j < m_nRows; ++j){
			curr = feature[j][i];
			if (j+1 < m_nRows){
				next = feature[j+1][i];
			}
			else{
				next = 0.0;
			}
		    retVal[j][i] = next-curr;
        }
    }
	return retVal;
}



