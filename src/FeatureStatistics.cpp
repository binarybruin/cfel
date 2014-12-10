/* What do we want to include? */
#include "FeatureStatistics.h"

// constructor/deconstructor

FeatureStatistics::FeatureStatistics(SAMPLE** feature, int nRows, int nCols, int sWinSize, int sHopSize){
	set_feature(feature);
	set_nRows(nRows);
	set_nCols(nCols);
	set_nStatCols();
	set_nStatRows();
	set_sWinSize(sWinSize);
	set_sHopSize(sHopSize);
	
	set_features();
	set_d1Features();
	set_d2Features();
}

FeatureStatistics::~FeatureStatistics(){
		
	// free feature
	for (int i = 0; i < nCols){
		free(m_feature[i]); 
	}
	free(m_freature);
	// free mean
	for (int i = 0; i < nCols){
		free(m_mean[i]); 
	}
	free(m_mean);
	// free std
	for (int i = 0; i < nCols){
		free(m_std[i]); 
	}
	free(m_std);
	// free var
	for (int i = 0; i < nCols){
		free(m_var[i]); 
	}
	free(m_var);
	
	// free d1Feature
	for (int i = 0; i < nCols){
		free(m_d1Feature[i]); 
	}
	free(m_d1Freature);
	// free d1Mean
	for (int i = 0; i < nCols){
		free(m_d1Mean[i]); 
	}
	free(m_d1Mean);
	// free d1Std
	for (int i = 0; i < nCols){
		free(m_d1Std[i]); 
	}
	free(m_d1Std);
	// free d1Var
	for (int i = 0; i < nCols){
		free(m_d1Var[i]); 
	}
	free(m_d1Var);
	
	// free d2Feature
	for (int i = 0; i < nCols){
		free(m_d2Feature[i]); 
	}
	free(m_d2Freature);
	// free d2Mean
	for (int i = 0; i < nCols){
		free(m_d2Mean[i]); 
	}
	free(m_d2Mean);
	// free d2Std
	for (int i = 0; i < nCols){
		free(m_d2Std[i]); 
	}
	free(m_d2Std);
	// free d2Var
	for (int i = 0; i < nCols){
		free(m_d2Var[i]); 
	}
	free(m_d2Var);
}


SAMPLE** get_feature(){
	return m_feature;
}

void set_feature(SAMPLE** feature){
	if (feature == NULL){
		return;
	}
	// memory allocation
	m_faeture 
	
	
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
	m_mean = (SAMPLE**)calloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; i++){
		m_mean[i] = (SAMPLE*)calloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_var = (SAMPLE**)calloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; i++){
		m_var[i] = (SAMPLE*)calloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_std = (SAMPLE**)calloc(m_nStatCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nStatCols; i++){
		m_std[i] = (SAMPLE*)calloc(m_nStatRows*sizeof(SAMPLE));
	}
	// computation	
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
	m_d1Feature = (SAMPLE**)calloc(m_nCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nCols; i++){
		m_mean[i] = (SAMPLE*)calloc(m_nRows*sizeof(SAMPLE));
	}
	m_d1Mean = (SAMPLE**)calloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; i++){
		m_d1Mean[i] = (SAMPLE*)calloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_d1Var = (SAMPLE**)calloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; i++){
		m_d1Var[i] = (SAMPLE*)calloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_d1Std = (SAMPLE**)calloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; i++){
		m_d1Std[i] = (SAMPLE*)calloc(m_nStatRows*sizeof(SAMPLE));
	}
	// calculate
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
	m_d2Feature = (SAMPLE**)calloc(m_nCols*sizeof(SAMPLE*));
	for (int i = 0; i < m_nCols; i++){
		m_d2Feature[i] = (SAMPLE*)calloc(m_nRows*sizeof(SAMPLE));
	}
	m_d2Mean = (SAMPLE**)calloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; i++){
		m_d2Mean[i] = (SAMPLE*)calloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_d2Var = (SAMPLE**)calloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; i++){
		m_d2Var[i] = (SAMPLE*)calloc(m_nStatRows*sizeof(SAMPLE));
	}
	m_d2Std = (SAMPLE**)calloc(m_nStatCols*sizeof(SAMPLE*));
	for (i = 0; i < m_nStatCols; i++){
		m_d2Std[i] = (SAMPLE*)calloc(m_nStatRows*sizeof(SAMPLE));
	
	// calculate
	m_d2Feature = calculate_delta(m_d1Feature);
	m_d2Mean = calcualte_mean(m_d2Feature);
	m_d2Var = calculate_var(m_d2Feature, m_d2Mean);
	m_d2Std = calculate_var2std(m_d2Var);
}


SAMPLE** calculate_mean(SAMPLE** feature){
	
	if (feature == NULL){
		printf("input is NULL");
		EXIT(1);
	}
	
	// memory allocation
	retVal 
	
	nRetRows = // number of return row
	
	//take column by column to compute mean within each hopping window
	for (int i = 0; i < nStatCols; i++){
		for (int j = 0; j < nStatRows; j ++){
			k = 0
			sum = 
			k++;
		}
		
	}
	
	return retVal;
}

SAMPLE** calculate_var(SAMPLE** feature, SAMPLE** mean){

}
SAMPLE** calculate_var2std(SAMPLE** var){

}
SAMPLE** calculate_delta(SAMPLE** feature){

}



