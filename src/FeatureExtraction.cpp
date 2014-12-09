/* What do we want to include? */
#include "FeatureExtraction.h"

using namespace FeatureExtraction;

// constructors

FeatureExtraction(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize){
	set_signal(signal);
	set_bufSize(bufSize);
	set_fs(fs);
	set_winSize(winSize);
	set_hopSize(hopSize);
} 

// getters and setters

SAMPLE* get_signal(){
	if (this->m_signal == NULL){
		printf("m_signal is null\n");
		return 1.0;
	}
	else{
		return this->m_singal;
	}
}

void set_signal(SAMPLE* signal){
	if (signal == NULL){
		printf("input signal is null\n");
		return;
	}
	else{
		this->m_signal = (SAMPLE*)malloc(sizeof(SAMPLE)*bufSize);
		this->m_signal = signal;
	}
}

int get_bufSize(){
	return this->m_bufSize;
}

void set_bufSize(int bufSize){
	this->m_bufSize = bufSize;
}

int get_fs(){
	return this->m_fs;
}

void set_fs(int fs){
	this->m_fs = fs;
}

int get_winSize(){
	return this->m_winSize;
}

void set_winSize(int winSize){
	this->m_winSize = winSize
}

int get_hopSize(){
	return this->m_hopSize;
}

void set_hopSize(int hopSize){
	this->m_hopSize = hopSize
}

// feature computation

int get_nRows(){
	return this->nRows;
}

int get_nCols(){
	return this->nCols;
}

float** get_feature(){
	return this->m_feature;
}

virtual void calculate_feature(){
	printf("Feature computed\n");
}

// preprocess

virtual void preprocess(){
}

