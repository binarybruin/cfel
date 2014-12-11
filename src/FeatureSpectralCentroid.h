//
// FeatureSpectralCentroid.h
//
// =================================================================== //
//
// Citygram feature class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/11/14
// C Programming, Fall 2014
//
// =================================================================== //

class FeatureSpectralCentroid: public FeatureExtraction
{
	private: 
		SAMPLE** magSpec;
		
	public:
		void calculate_feature();
}