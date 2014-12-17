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
#include <stdlib.h>

// constructor/deconstructor
FeatureStatistics::FeatureStatistics(FeatureExtraction* featureObject, int sWinSize, int sHopSize){
	
	set_featureObject(FeatureExtraction* featureObject);
	
	
	set_sWinSize(sWinSize);
	set_sHopSize(sHopSize);
	calculate_nStatCols(); // no input; computed from nCols
	calculate_nStatRows(); // no input; computed from nRows and sHopSize
	
	set_features();
	set_d1Features();
	set_d2Features();
}

FeatureStatistics::~FeatureStatistics(){
	
	int nStatCols = this->get_nStatRows();
	
	// free mean
	if (m_mean != NULL){
		for (int i = 0; i < nStatRows; ++i){// 
			free(m_mean[i]); 
		}
		free(m_mean);
	}
	// free stds
	if (m_std != NULL){
		for (int i = 0; i < nStatRows; ++i){ //
			free(m_std[i]); 
		}
		free(m_std);
	}
	// free var
	if (m_var != NULL){
		for (int i = 0; i < nStatRows; ++i){ //
			free(m_var[i]); 
		}
		free(m_var);
	}
	
	int nRows = this->get_featureObject()->get_nRows();
	
	// free d1Feature
	if (m_d1Feature != NULL){
		for (int i = 0; i < nRows; ++i){
			free(m_d1Feature[i]); 
		}
		free(m_d1Freature);
	}
	// free d1Mean
	if (m_d1Mean != NULL){
		for (int i = 0; i < nStatRows; ++i){
			free(m_d1Mean[i]); 
		}
		free(m_d1Mean);
	}
	// free d1Std
	if (m_d1Std != NULL){
		for (int i = 0; i < nStatRows; ++i){
			free(m_d1Std[i]); 
		}
		free(m_d1Std);
	}
	// free d1Var
	if (m_d1Var != NULL){
		for (int i = 0; i < nStatRows; ++i){
			free(m_d1Var[i]); 
		}
		free(m_d1Var);
	}
	
	// free d2Feature
	if (m_d2Feature != NULL){
		for (int i = 0; i < nrows; ++i){
			free(m_d2Feature[i]); 
		}
		free(m_d2Freature);
	}
	// free d2Mean
	if (m_d2Mean != NULL){
		for (int i = 0; i < nStatRows; ++i){
			free(m_d2Mean[i]); 
		}
		free(m_d2Mean);
	}
	// free d2Std
	if (m_d2Std != NULL){
		for (int i = 0; i < nStatRows; ++i){
			free(m_d2Std[i]); 
		}
		free(m_d2Std);
	}
	// free d2Var
	if (m_d2Var != NULL){
		for (int i = 0; i < nStatRows; ++i){
			free(m_d2Var[i]); 
		}
		free(m_d2Var);
	}
}

FeatureExtraction* 	get_featureObject(){
	return m_featureObject;
}

void set_featureObject(FeatureExtraction* featureObject){
	m_featureObject = featureObject;
}

int FeatureStatistics::get_nStatRows(){
	return m_nStatRows;
}

void FeatureStatistics::calculate_nStatRows(){
	int nRows = this->get_featureObject()->get_nRows();
	int sHopSize = this->get_sHopSize();
	this->m_nStatRows =  ceil(nRows/(double)sHopSize);
}

int FeatureStatistics::get_nStatCols(){
	return m_nStatCols;
}

void FeatureStatistics::calculate_nStatRows(){
	int nCols = this->get_featureObject()->get_nCols(); 
	this->m_nStatCols = nCols;
}

int FeatureStatistics::get_sWinSize(){
	return m_sWinSize;
}

void FeatureStatistics::set_sWinSize(int sWinSize){
	m_sWinSize = sWinSize;
}

int FeatureStatistics::get_sHopSize(){
	return m_sHopSize;
}

void FeatureStatistics::set_sHopSize(int sHopSize){
	m_sHopSize = sHopSize;
}

SAMPLE** FeatureStatistics::get_mean(){
	return m_mean;
}

SAMPLE** FeatureStatistics::get_std(){
	return m_std;
}

SAMPLE** FeatureStatistics::get_var(){
	return m_var;
}

void FeatureStatistics::set_d0features(){
	// memory allocation
	this->m_mean = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
		m_mean[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	this->m_var = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
		m_var[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	this->m_std = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
		m_std[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	
	// calculate feature variables
	SAMPLE** feature = this->get_featureObject()->get_feature()
	m_mean = calcualte_mean(feature);
	m_var = calculate_var(feature, m_mean);
	m_std =calculate_var2std(m_var);
}



SAMPLE** FeatureStatistics::get_d1Feature(){
	return m_d1Feature;
}

SAMPLE** FeatureStatistics::get_d1Mean(){
	return m_d1Mean;
}

SAMPLE** FeatureStatistics::get_d1Std(){
	return m_d1Std;
}

SAMPLE** FeatureStatistics::get_d1Var(){
	return m_d1Var;
}

void FeatureStatistics::set_d1Features(){
	// memory allocation
	m_d1Feature = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nCols; ++i){
		m_d1Feature[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE));
	}
	m_d1Mean = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
		m_d1Mean[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_d1Var = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
		m_d1Var[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_d1Std = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
		m_d1Std[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	
	// calculate d1 feature variables
	SAMPLE** feature = this->get_featureObject()->get_feature()
	m_d1Feature = calculate_delta(feature);
	m_d1Mean = calcualte_mean(m_d1Feature);
	m_d1Var = calculate_var(m_d1Feature, m_d1Mean);
	m_d1Std = calculate_var2std(m_d1Var);
}

SAMPLE** FeatureStatistics::get_d2Feature(){
	return m_d2Feature;
}

SAMPLE** FeatureStatistics::get_d2Mean(){
	return m_d2Mean; 
}

SAMPLE** FeatureStatistics::get_d2Std(){
	return m_d2Std;
}

SAMPLE** FeatureStatistics::get_d2Var(){
	return m_d2Var;
}



void FeatureStatistics::set_d2Features(){
	// memory allocation
	m_d2Feature = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nCols; ++i){
		m_d2Feature[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE));
	}
	m_d2Mean = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
		m_d2Mean[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_d2Var = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
		m_d2Var[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_d2Std = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
		m_d2Std[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
	}
	
	// calculate
	SAMPLE** feature = this->get_d1Feature();
	m_d2Feature = calculate_delta(feature);
	m_d2Mean = calcualte_mean(m_d2Feature);
	m_d2Var = calculate_var(m_d2Feature, m_d2Mean);
	m_d2Std = calculate_var2std(m_d2Var);
}


SAMPLE** FeatureStatistics::calculate_mean(SAMPLE** feature){
	// input check
	if (feature == NULL){
		printf("input is NULL\n");
		exit(1);
	}
	
	// memory allocation
	SAMPLE** retVal  = (SAMPLE**)malloc(nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < nStatCols; ++i){
        retVal[i] = (SAMPLE*)malloc(nStatRows*sizeof(SAMPLE));
    }
	
	//take column by column to compute mean within each hopping window	
	SAMPLE sum;
	SAMPLE val;
	for (int i = 0; i < m_nStatCols; ++i){
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


SAMPLE** FeatureStatistics::calculate_var(SAMPLE** feature, SAMPLE** mean){
	// input check
	if (feature == NULL | mean == NULL){
		printf("input is NULL\n");
		exit(1);
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
	for (int i = 0; i < m_nStatCols; ++i){
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


SAMPLE** FeatureStatistics::calculate_var2std(SAMPLE** var){
	// input check
	if (var == NULL){
		printf("input is NULL\n");
		exit(1);
	}

	// memory allocation
	SAMPLE** retVal  = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
        retVal[i] = (SAMPLE*)malloc(m_nStatRows*sizeof(SAMPLE));
    }
	
	// std calculation
	for (int i = 0; i < m_nStatCols; ++i){
		for (int j = 0; j < m_nStatRows; ++j){
		    retVal[j][i] = sqrt(var[j][i]);
        }
    }
    return retVal;
}


SAMPLE** FeatureStatistics::calculate_delta(SAMPLE** feature){
	// input check
	if (feature == NULL){
		printf("input is NULL\n");
		exit(1);
	}

	// memory allocation
	SAMPLE** retVal  = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
        retVal[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE));
    }
	
	// difference calculation
	SAMPLE curr;
	SAMPLE next;
	for (int i = 0; i < m_nCols; ++i){
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



