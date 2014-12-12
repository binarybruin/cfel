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

FeatureExtractionSpectral(){
}

~FeatureExtractionSpectral(){
}


int get_nWins(){
	return m_nWins;
}

void set_nWins(int nWins){
	m_nWins = nWins;
}


int get_winType(){
	return m_winType;
	/* 	1: Hann 
		2: Hamming 
		3: Blackman
		4: Tukey
		5: Kaiser
	*/
}
void set_winType(int winType){
	if (winType > m_nWins){
		printf("Check your input");
		EXIT(1);
	}
	m_winType = winType;
}
		
SAMPLE** get_window(){
	return m_window;
}

void set_window(){
	/* 	1: Hann 
		2: Hamming 
		3: Blackman
		4: Tukey
		5: Kaiser
	*/
	m_window = (SAMPLE**)malloc(sizeof(SAMPLE)*); // rows and columns...?
	for (int i = 0; i < numWin; ++i){
	}
}

void calculate_FFT(){
}


void calculate_magSpec(){

	magSpec = (SAMPLE**)malloc(nWinSize*sizeof(SAMPLE*));
	
	for (int i = 0; i < nWinSize; ++i){
		magSpec[i] = (SAMPLE*)malloc(nRows*sizeof(SAMPLE*));
	}

	// get the magnitude spectrum of the complex fft result
	for (int i = 0; i < nNumSamples/2+1; i++)
		magSpec[i] = abs(fftOut[i]);

	return magSpec;
}

