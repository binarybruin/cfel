#pragma once
#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <complex>
#include <stdlib.h>

typedef double SAMPLE;

class FeatureExtractionRMS {

private:
	// input parameters
	SAMPLE*			m_signal;
	int				m_bufSize;
	int				m_fs;
	int				m_winSize;
	int				m_hopSize;
	//int				initTime;

	// output parameters
	//float*			m_featureTime;
	SAMPLE**		m_feature;
	int				m_nRows;
	int				m_nCols;

public:
	FeatureExtractionRMS(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize);
	~FeatureExtractionRMS();

	SAMPLE*			get_signal();
	void			set_signal(SAMPLE* signal);
	int				get_bufSize();
	void			set_bufSize(int bufSize);
	int				get_fs();
	void			set_fs(int fs);
	int				get_winSize();
	void			set_winSize(int winSize);
	int				get_hopSize();
	void			set_hopSize(int hopSize);

	int				get_nRows();
	void			set_nRows(int nRows);
	int				get_nCols();
	void			set_nCols(int nCols);
	SAMPLE**		get_feature();
	void			calculate_feature();

};

FeatureExtractionRMS::FeatureExtractionRMS(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize){
	set_signal(signal);
	set_bufSize(bufSize);
	set_fs(fs);
	set_winSize(winSize);
	set_hopSize(hopSize);
	calculate_feature();
}

FeatureExtractionRMS::~FeatureExtractionRMS(){
	if (m_signal != NULL){
		free(m_signal);
	}

	if (m_feature != NULL){
		for (int i = 0; i < m_nCols; i++){
			free(m_feature[i]);
		}
	}
}

// getters and setters

SAMPLE* FeatureExtractionRMS::get_signal(){
	if (this->m_signal == NULL){
		printf("m_signal is null\n");
		exit(1);
	}
	else{
		return this->m_signal;
	}
}

void FeatureExtractionRMS::set_signal(SAMPLE* signal){
	if (signal == NULL){
		printf("input signal is null\n");
		return;
	}
	else{
		int bufSize = get_bufSize();
		this->m_signal = (SAMPLE*)malloc(sizeof(SAMPLE)*bufSize);
		this->m_signal = signal;
	}
}

int FeatureExtractionRMS::get_bufSize(){
	return this->m_bufSize;
}

void FeatureExtractionRMS::set_bufSize(int bufSize){
	this->m_bufSize = bufSize;
}

int FeatureExtractionRMS::get_fs(){
	return this->m_fs;
}

void FeatureExtractionRMS::set_fs(int fs){
	this->m_fs = fs;
}

int FeatureExtractionRMS::get_winSize(){
	return this->m_winSize;
}

void FeatureExtractionRMS::set_winSize(int winSize){
	this->m_winSize = winSize;
}

int FeatureExtractionRMS::get_hopSize(){
	return this->m_hopSize;
}

void FeatureExtractionRMS::set_hopSize(int hopSize){
	this->m_hopSize = hopSize;
}

// feature computation

int FeatureExtractionRMS::get_nRows(){
	return this->m_nRows;
}

void FeatureExtractionRMS::set_nRows(int nRows){
	this->m_nRows = nRows;
}

int FeatureExtractionRMS::get_nCols(){
	return this->m_nCols;
}

void FeatureExtractionRMS::set_nCols(int nCols){
	this->m_nCols = nCols;
}

SAMPLE** FeatureExtractionRMS::get_feature(){
	return this->m_feature;
}

void FeatureExtractionRMS::calculate_feature(){
	int bufSize = this->get_bufSize();
	int hopSize = this->get_hopSize();
	int winSize = this->get_winSize();
	SAMPLE* buffer = this->get_signal();

	// set nCols and nRows (move to somewhere else?)
	set_nCols(1);
	set_nRows(ceil(bufSize / (double)hopSize));
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
				if (j*hopSize + k < bufSize - 1){ // conceptually zero-padding
					// check the sign of two consecutive samples
					if (buffer[j*hopSize + k] < 0 && buffer[j*hopSize + k + 1] > 0){
						++zcc;
					}
					if (buffer[j*hopSize + k] > 0 && buffer[j*hopSize + k + 1] < 0){
						++zcc;
					}
				}
			}
			m_feature[j][i] = (SAMPLE)zcc / winSize;
		}
	}
}


class FeatureStatistics { // put this class inside FeatureExtr class?
private:
	// input parameters
	FeatureExtraction* m_featureObject;
	int 			m_sWinSize; // statistics winSize
	int 			m_sHopSize; // statistics hopSize
	int				m_nStatRows;
	int				m_nStatCols;
	//SAMPLE* featureTime;

	// output parameters
	int 			m_nStatRows;
	int 			m_nStatCols;
	// 1) stats of original values
	SAMPLE** 		m_mean; // mean
	SAMPLE** 		m_std;  // standard deviation
	SAMPLE** 		m_var;  // variance
	// 2) stats of first derivatives
	SAMPLE** 		m_d1Feature; // first derivatives of feature
	SAMPLE** 		m_d1Mean;
	SAMPLE** 		m_d1Std;
	SAMPLE** 		m_d1Var;
	// 3) stats of second derivatives
	SAMPLE** 		m_d2Feature; // second derivatives of feature
	SAMPLE** 		m_d2Mean;
	SAMPLE** 		m_d2Std;
	SAMPLE** 		m_d2Var;
	//SAMPLE* statTime;

public:
	FeatureStatistics(FeatureExtractionRMS featureObject, int sWinSize, int sHopSize);
	~FeatureStatistics();

	SAMPLE** 		get_feature();
	void 			set_feature(SAMPLE** feature);
	int 			get_nRows();
	void 			set_nRows(int nRow);
	int 			get_nCols();
	void 			set_nCols(int nCol);
	int 			get_sWinSize();
	void 			set_sWinSize(int sWinSize);
	int 			get_sHopSize();
	void 			set_sHopSize(int sHopSize);
	//SAMPLE* get_featureTime();
	// void set_featureTime()

	SAMPLE** 		get_mean();
	SAMPLE** 		get_std();
	SAMPLE** 		get_var();
	void 			set_features(); // set features and nStatCols/nStatRows

	SAMPLE** 		get_d1Feature();
	SAMPLE** 		get_d1Mean();
	SAMPLE** 		get_d1Std();
	SAMPLE** 		get_d1Var();
	void 			set_d1Features();


	SAMPLE** 		get_d2Feature();
	SAMPLE** 		get_d2Mean();
	SAMPLE** 		get_d2Std();
	SAMPLE** 		get_d2Var();
	void 			set_d2Features();

	SAMPLE** 		calculate_mean(SAMPLE** feature); // general mean calculator
	SAMPLE** 		calculate_var(SAMPLE** feature, SAMPLE** mean); // general var calculator
	SAMPLE** 		calculate_var2std(SAMPLE** var); // general var to std converters
	SAMPLE** 		calculate_delta(SAMPLE** feature); // generla delta calculator
};

FeatureStatistics::FeatureStatistics(FeatureExtractionRMS featureObject, int sWinSize, int sHopSize){
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

FeatureStatistics::~FeatureStatistics(){
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


SAMPLE** FeatureStatistics::get_feature(){
	return m_feature;
}

void FeatureStatistics::set_feature(SAMPLE** feature){
	// input check
	if (feature == NULL){
		EXIT(1);
	}

	// memory allocation 
	if (m_feature == NULL){ // is a pointer NULL by default when declared?
		m_feature = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*));
		for (int i = 0; i < m_nCols; ++i){
			m_feature[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE));
		}
	}

	// set feature
	m_feature = feature;
}

int FeatureStatistics::get_nRows(){
	return m_nRows
}

void FeatureStatistics::set_nRows(int nRows){
	m_nRows = nRows;
}

int FeatureStatistics::get_nCols(){
	return m_nCols;
}

void FeatureStatistics::set_nCols(int nCols){
	m_nCols = nCols;
}

int FeatureStatistics::get_nStatRows(){
	return m_nStatRows;
}

void FeatureStatistics::set_nStatRows(){
	m_nStatRows = ceil(m_nRows / m_nHopSize);
}

int FeatureStatistics::get_nStatCols(){
	return m_nStatCols;
}

void FeatureStatistics::set_nStatRows(){
	m_nStatCols = m_nCols;
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

void FeatureStatistics::set_features(){
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
	m_std = calculate_var2std(m_var);
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
	m_d1Feature = calculate_delta(m_feature);
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
	m_d2Feature = calculate_delta(m_d1Feature);
	m_d2Mean = calcualte_mean(m_d2Feature);
	m_d2Var = calculate_var(m_d2Feature, m_d2Mean);
	m_d2Std = calculate_var2std(m_d2Var);
}


SAMPLE** FeatureStatistics::calculate_mean(SAMPLE** feature){
	// input check
	if (feature == NULL){
		printf("input is NULL");
		EXIT(1);
	}

	// memory allocation
	SAMPLE** retVal = (SAMPLE**)malloc(nStatCols*sizeof(SAMPLE*));
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
				if (j*m_sHopSize + k >= m_nRows){
					val = 0;
				}
				else{
					val = feature[j*m_sHopSize + k][i];
				}
				sum += val;
			}
			retVal[j][i] = sum / m_sWinSIze;
		}
	}
	return retVal;
}


SAMPLE** FeatureStatistics::calculate_var(SAMPLE** feature, SAMPLE** mean){
	// input check
	if (feature == NULL | mean == NULL){
		printf("input is NULL");
		EXIT(1);
	}

	// memory allocation
	SAMPLE** retVal = (SAMPLE**)malloc(nStatCols*sizeof(SAMPLE*));
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
				if (j*m_sHopSize + k >= m_nRows){ // zero-padding
					val = 0;
				}
				else{
					val = feature[j*m_sHopSize + k][i];
				}
				dif = val - mean[j][i];
				sqrSum += dif*dif;
			}
			retVal[j][i] = sqrSum / (m_sWinSIze - 1);
		}
	}
	return retVal;
}


SAMPLE** FeatureStatistics::calculate_var2std(SAMPLE** var){
	// input check
	if (var == NULL){
		printf("input is NULL");
		EXIT(1);
	}

	// memory allocation
	SAMPLE** retVal = (SAMPLE**)malloc(m_nStatCols*sizeof(SAMPLE*));
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
		printf("input is NULL");
		exit(1);
	}

	int nCols = this->get_featureObject()->get_nCols();

	// memory allocation
	SAMPLE** retVal = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; ++i){
		retVal[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE));
	}

	// difference calculation
	SAMPLE curr;
	SAMPLE next;
	for (int i = 0; i < m_nCols; ++i){
		for (int j = 0; j < m_nRows; ++j){
			curr = feature[j][i];
			if (j + 1 < m_nRows){
				next = feature[j + 1][i];
			}
			else{
				next = 0.0;
			}
			retVal[j][i] = next - curr;
		}
	}
	return retVal;
}



int main(){

	SAMPLE signal[44100];
	int	bufSize = 44100;
	int	winSize = 4410;
	int	hopSize = 44090;
	int fs = 44100;
	for (int i = 0; i < fs; ++i){
		signal[i] = ((double)rand() / (RAND_MAX)) * 2 - 1;
	}

	std::cout << signal[100] << std::endl;
	std::cout << signal[1000] << std::endl;
	std::cout << signal[10000] << std::endl;

	FeatureExtractionRMS* rmsObj = new FeatureExtractionRMS(signal, bufSize, fs, winSize, hopSize);
	FeatureRMS* featureObjRMS = new FeatureEXtractionRMS(si)


	std::cout << rmsObj->get_nCols() << std::endl;
	std::cout << rmsObj->get_nRows() << std::endl;
	std::cout << rmsObj->get_bufSize() << std::endl;
	std::cout << rmsObj->get_hopSize() << std::endl;
	std::cout << rmsObj->get_winSize() << std::endl;

	SAMPLE* signal2 = rmsObj->get_signal();
	SAMPLE** feature = rmsObj->get_feature();

	std::cout << signal2[100] << std::endl;
	std::cout << signal2[1000] << std::endl;
	std::cout << signal2[10000] << std::endl;

	for (int i = 0; i < 2; i++){
		std::cout << "ZCR	:" << feature[i][0] << std::endl;
	}

	return 0;
}
