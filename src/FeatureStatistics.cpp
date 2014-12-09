/* What do we want to include? */
#include "FeatureStatistics.h"

/* constructors and deconstructors */

FeatureStatistics::FeatureStatistics(FeatureExtraction featureObject){
	
	// Get input parameters
	m_feature = (SAMPLE**)malloc(nCols*sizeof(SAMPLE*));
	for (int i = 0; i < nCols; i++){
		m_feature[i] = (SAMPLE*)calloc(nRows*sizeof(SAMPLE));
	}
	m_feature = featureObject.feature;
	
	m_nRows = featureObject.nRows;
	m_nCols = featureObject.nCols;
	
	m_sWinSize = systemObject.sWinSize;
	m_sHopSize = systemObject.sHopSize;

	// Calculate output parameters
	calculate_mean();
	calculate_std();
	calculate_var();

	calculate_d1Feature();
	calculate_d1Mean();
	calculate_d1Std();s
	calculate_d1Var();

	calculate_d2Feature();
	calculate_d2Mean();
	calculate_d2Std();
	calculate_d2Var();
}

FeatureStatistics::~FeatureStatistics(){
	
	
	/* FREE ORIGINAL FEATURE */
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
	
	
	/* FREE D1 FEATURE */
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
	
	
	/* FREE D2 FEATURE */
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

/* getters and setters */




/* calculators */



