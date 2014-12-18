//
// FeatureExtraction.cpp
//
// =================================================================== //
//
// Citygram feature class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/11/14
// C Programming, Fall 2014
//
// =================================================================== //

#include "FeatureExtraction.h"
#include <stdlib.h>

// constructor/deconstructor

FeatureExtraction::FeatureExtraction(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize){
	set_signal(signal);
	set_bufSize(bufSize);
	set_fs(fs);
	set_winSize(winSize);
	set_hopSize(hopSize);
	//calculate_feature();
} 

FeatureExtraction::~FeatureExtraction(){
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

SAMPLE* FeatureExtraction::get_signal(){
	if (this->m_signal == NULL){
		printf("m_signal is null\n");
		exit(1);
	}
	else{
		return this->m_signal;
	}
}

void FeatureExtraction::set_signal(SAMPLE* signal){
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

int FeatureExtraction::get_bufSize(){
	return this->m_bufSize;
}

void FeatureExtraction::set_bufSize(int bufSize){
	this->m_bufSize = bufSize;
}

int FeatureExtraction::get_fs(){
	return this->m_fs;
}

void FeatureExtraction::set_fs(int fs){
	this->m_fs = fs;
}

int FeatureExtraction::get_winSize(){
	return this->m_winSize;
}

void FeatureExtraction::set_winSize(int winSize){
	this->m_winSize = winSize;
}

int FeatureExtraction::get_hopSize(){
	return this->m_hopSize;
}

void FeatureExtraction::set_hopSize(int hopSize){
	this->m_hopSize = hopSize;
}

// feature computation

int FeatureExtraction::get_nRows(){
	return this->m_nRows;
}

void FeatureExtraction::set_nRows(int nRows){
	this->m_nRows = nRows;
}

int FeatureExtraction::get_nCols(){
	return this->m_nCols;
}

void FeatureExtraction::set_nCols(int nCols){
	this->m_nCols = nCols;
}


SAMPLE** FeatureExtraction::get_feature(){
	return this->m_feature;
}

void FeatureExtraction::new_feature(int nRows, int nCols){
	m_feature = (SAMPLE**)malloc(nRows*sizeof(SAMPLE*));
	for (int i = 0; i < nCols; ++i){
		m_feature[i] = (SAMPLE*)malloc(nCols*sizeof(SAMPLE));
	}
}

SAMPLE** FeatureExtraction::calculate_feature(){
	return m_feature;
}

// preprocess

void FeatureExtraction::preprocess(){
	return;
}

