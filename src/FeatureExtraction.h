//
// FeatureExtraction.h
//
// =================================================================== //
//
// Citygram feature class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/8/14
// C Programming, Fall 2014
//
// =================================================================== //

#ifndef __CFEL__FeatureExtraction__
#define __CFEL__FeatureExtraction__

#include <stdio.h>
#include <math.h>

#include "FeatureSystem.h"

typedef double SAMPLE;

class FeatureExtraction {
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
		float**			m_feature;
		int				m_nRows;
		int				m_nCols;


	public:
		FeatureExtraction(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize);

		SAMPLE*			get_signal();
		void			set_signal(float* signal);
		int				get_bufSize();
		void			set_bufSize(int bufSize);
		int				get_fs();
		void			set_fs(int fs);
		int				get_winSize();
		void			set_winSize(int winSize);
		int				get_hopSize();
		void			set_hopSize(int hopSize);
		
		virtual void	preprocess();

		SAMPLE**		get_feature();
		virtual void	calculate_feature();
		int				get_nRows();
		int				get_nCols();
};

#endif