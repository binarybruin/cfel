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


class FeatureExtractionSpectral: public FeatureExtraction
{

	private: 
		// borrow FFT function from external library...
		int m_nWins
		int m_winType;
		SAMPLE** m_window;
		SAMPLE** m_magSpec;

	public:
		
		FeatureExtractionSpectral();
		~FeatureExtractionSPectral();
		
		int get_nWins();
		void set_nWins(int nWins);
		
		int get_winType();
		void set_winType(int winType);
		
		SAMPLE* get_window();
		void calculate_window();
		
		SAMPLE* calculate_FFT();
		
		SAMPLE** calculate_magSpec();
}