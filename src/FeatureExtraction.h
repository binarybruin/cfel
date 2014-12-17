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

typedef double SAMPLE;

class FeatureExtraction {
	private:
		// input parameters
		SAMPLE*			m_signal;
		int				m_bufSize;
		int				m_fs;
		int				m_winSize;
		int				m_hopSize;

		// output parameters
		SAMPLE**		m_feature;
		int				m_nRows;
		int				m_nCols;

	public:
		FeatureExtraction(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize);
		~FeatureExtraction();

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
		void			set_nRows();
		int				get_nCols();
		void			set_nCols();
		SAMPLE**		get_feature();
		virtual void	calculate_feature();
		
		virtual void	preprocess();
};

#endif