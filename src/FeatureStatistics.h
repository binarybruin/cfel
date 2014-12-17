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

#include "FeatureExtraction.h"

class FeatureStatistics 
{
	private:
		// input parameters
		FeatureExtraction* m_featureObject;
		int 			m_sWinSize; // statistics winSize
		int 			m_sHopSize; // statistics hopSize
		int				m_nStatRows;
		int				m_nStatCols;
		
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

	public:
		FeatureStatistics(FeatureExtraction* featureObject, int sWinSize, int sHopSize);
		~FeatureStatistics();

		FeatureExtraction* 	get_featureObject();
		void 			set_featureObject(FeatureExtraction* featureObject);
		int 			get_sWinSize();
		void 			set_sWinSize(int sWinSize);
		int 			get_sHopSize();
		void 			set_sHopSize(int sHopSize);
		int 			get_nStatRows();
		void 			calculate_nStatRows();
		int 			get_nStatCols();
		void 			calculaate_nStatCols();
		 
		SAMPLE** 		get_mean();
		SAMPLE** 		get_std();
		SAMPLE** 		get_var();
		void 			set_d0features(); // set features and nStatCols/nStatRows
		
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

#endif