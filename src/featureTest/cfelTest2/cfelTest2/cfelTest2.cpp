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

	std::cout << "works fine till memory allocation\n";
	// allocate memory for feature
	m_feature = (SAMPLE**)malloc(nRows*sizeof(SAMPLE*));
	for (int i = 0; i < nRows; ++i){
		m_feature[i] = (SAMPLE*)malloc(nCols*sizeof(SAMPLE));
	}
	std::cout << "memory allocated\n";
	
	// RMS calculation
	SAMPLE sqrSum;
	SAMPLE val;
	for (int i = 0; i < nCols; ++i){
		for (int j = 0; j < nRows; ++j){
			sqrSum = 0.0;
			for (int k = 0; k < winSize; ++k){
				if (j*hopSize + k >= bufSize){ // conceptually zero-padding
					val = 0;
				}
				else{
					val = buffer[j*hopSize + k];
				}
				sqrSum += val*val;
			}
			m_feature[j][i] = sqrt(sqrSum / (SAMPLE)winSize);
		}
	}
}



int main(){

	SAMPLE signal[44100];
	int	bufSize = 44100;
	int	winSize = 1024;
	int	hopSize = 44090;
	int fs = 44100;
	for (int i = 0; i < fs; ++i){
		signal[i] = ((double)rand() / (RAND_MAX)) * 2 - 1;
	}

	std::cout << signal[100] << std::endl;
	std::cout << signal[1000] << std::endl;
	std::cout << signal[10000] << std::endl;

	FeatureExtractionRMS* rmsObj = new FeatureExtractionRMS(signal, bufSize, fs, winSize, hopSize);

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
		std::cout << "RMS	:" << feature[i][0] << std::endl;
	}
	return 0;
}
