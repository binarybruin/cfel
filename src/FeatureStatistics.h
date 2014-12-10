//
// FeatureStatistics.h
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

#ifndef __CFEL__FeatureStatistics__
#define __CFEL__FeatureStatistics__

#include <stdio.h>
#include <math.h>

#include "FeatureSystem.h"
#include "FeatureExtraction.h"

class FeatureStatistics { // put this class inside FeatureExtr class?
	private:
		// input parameters
		SAMPLE** m_feature; 
		int m_nRows;
		int m_nCols;
		int m_sWinSize; // statistics winSize
		int m_sHopSize; // statistics hopSize
		//SAMPLE* featureTime;
		
		// output parameters
		int m_nStatRows;
		int m_nStatCols;
		// 1) stats of original values
		SAMPLE** m_mean; // mean
		SAMPLE** m_std;  // standard deviation
		SAMPLE** m_var;  // variance
		// 2) stats of first derivatives
		SAMPLE** m_d1Feature; // first derivatives of feature
		SAMPLE** m_d1Mean;
		SAMPLE** m_d1Std;
		SAMPLE** m_d1Var;
		// 3) stats of second derivatives
		SAMPLE** m_d2Feature; // second derivatives of feature
		SAMPLE** m_d2Mean;
		SAMPLE** m_d2Std;
		SAMPLE** m_d2Var;
		//SAMPLE* statTime;

	public:
		FeatureStatistics(FeatureExtraction featureObject);
		~FeatureStatistics();

		SAMPLE** get_feature();
		void set_feature(SAMPLE** feature);
		int get_nRows(); 
		void set_nRows(int nRow);
		int get_nCols();
		void set_nCols(int nCol);
		int get_sWinSize();
		void set_sWinSize(int sWinSize);
		int get_sHopSize();
		void set_sHopSize(int sHopSize);
		//SAMPLE* get_featureTime();
		// void set_featureTime()
		 
		SAMPLE** get_mean();
		SAMPLE** get_std();
		SAMPLE** get_var();
		void set_features(); // set features and nStatCols/nStatRows
		
		SAMPLE** get_d1Feature();
		SAMPLE** get_d1Mean();
		SAMPLE** get_d1Std();
		SAMPLE** get_d1Var();
		void set_d1Features();
		
		
		SAMPLE** get_d2Feature();
		SAMPLE** get_d2Mean();
		SAMPLE** get_d2Std();
		SAMPLE** get_d2Var();
		void set_d2Features();
				
		SAMPLE** calculate_mean(SAMPLE** feature); // general mean calculator
		SAMPLE** calculate_var(SAMPLE** feature, SAMPLE** mean); // general var calculator
		SAMPLE** calculate_var2std(SAMPLE** var); // general var to std converters
		SAMPLE** calculate_delta(SAMPLE** feature); // generla delta calculator
};
