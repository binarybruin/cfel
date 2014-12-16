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

class FeatureExtractionSpectral: public FeatureExtraction
{

    private:
        // borrow FFT function from external library...
        int m_winType;
        SAMPLE** m_magSpec;

<<<<<<< HEAD
	public:
		
		FeatureExtractionSpectral();
		~FeatureExtractionSpectral();
		
		int get_winType();
		void set_winType(int winType);
		SAMPLE** get_magSpec();
		void calculate_magSpec();
};

#endif
=======
    public:

        FeatureExtractionSpectral();
        ~FeatureExtractionSPectral();

        int get_winType();
        void set_winType(int winType);

        SAMPLE** get_magSpec();
        void calculate_magSpec();
}
>>>>>>> 1c1f6c4c216f142add73ba11e9703fa576998778
