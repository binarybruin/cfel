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

using namespace FeatureExtraction;

// constructor/deconstructor

FeatureExtraction::FeatureExtraction(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize){
	set_signal(signal);
	set_bufSize(bufSize);
	set_fs(fs);
	set_winSize(winSize);
	set_hopSize(hopSize);
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

int FeatureExtractionRMS::get_nCols(){
	return this->m_nCols;
}

SAMPLE** FeatureExtractionRMS::get_feature(){
	return this->m_feature;
}

virtual FeatureExtractionRMS::void calculate_feature(){
	printf("Feature computed\n");
}

// preprocess

virtual void preprocess(){
}

