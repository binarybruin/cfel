//
// FeatureExtractionSpectral.cpp
//
// =================================================================== //
//
// Citygram FeatureSpectralSpectral class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/12/14
// C Programming, Fall 2014
//
// =================================================================== //

#ifndef __CFEL__FeatureExtractionSpectral__
#define __CFEL__FeatureExtractionSpectral__

#include "FeatureExtraction.h"
#include "Utils/WindowFunction.h"
#include "Utils/FFT.h"

class FeatureExtractionSpectral
{

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

		// spectral
        WindowType m_winType;
		SAMPLE m_fBinSize;
        SAMPLE** m_magSpec;

    public:

        FeatureExtractionSpectral(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize, WindowType winType);
        ~FeatureExtractionSpectral();

		// feature extraction getters/setters
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
		void			set_nRows(int nRows);
		int				get_nCols();
		void			set_nCols(int nCols);
		void			new_feature(int nRows, int nCols);
		SAMPLE**		get_feature();

		virtual SAMPLE**	calculate_feature();

		virtual void	preprocess();

		// spectral
        WindowType get_winType();
        void set_winType(WindowType winType);
		
		SAMPLE get_fBinSize();
		void calculate_fBinSize();
		
        SAMPLE** get_magSpec();
        void calculate_magSpec();
};

#endif