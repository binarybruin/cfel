/* What do we want to include? */
#include "FeatureExtraction.h"

using namespace FeatureExtraction;

// constructors

FeatureExtraction(SAMPLE* signal, int bufferSize, int fs, int winSize, int hopSize){
	set_signal(sginal);
	set_bufSize(
} 

// getters and setters

float* get_signal(){
	if (this->m_signal == NULL){
		printf("m_signal is null\n");
		return 1.0;
	}
	else{
		return this->m_singal;
	}
}

void set_signal(float* signal){
	if (signal == NULL){
		printf("signal is null\n");
		return;
	}
	else{
		this->m_signal = signal;
	}
}

int get_bufferSize(){
	return this->m_bufferSize;
}

void set_bufferSize(int bufferSize){
	this->m_bufferSize = bufferSize;
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
	return this->m_winSize;
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

