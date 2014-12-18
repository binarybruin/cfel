// cfelTestSpecCent.cpp : Defines the entry point for the console application.
//

#include <algorithm>

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <complex>
#define M_PI 3.14
typedef double SAMPLE;
enum WindowType {
	WINDOW_TYPE_RECTANGULAR = 0,
	WINDOW_TYPE_BARTLETT,
	WINDOW_TYPE_HANNING,
	WINDOW_TYPE_HAMMING,
	WINDOW_TYPE_BLACKMAN,
	NUM_WINDOW_TYPES
};

class WindowFunction {
private:
	WindowType m_winType;
	int m_winSize;
	SAMPLE* m_window;

public:
	WindowFunction(int winSize);
	WindowFunction(int winSize, WindowType winType);
	~WindowFunction();

	void set_winType(WindowType winType);
	WindowType get_winType();

	void set_winSize(int winSize);
	int get_winSize();

	SAMPLE* get_window();
	void calculate_window();
};

WindowFunction::WindowFunction(int winSize) {
	m_winType = WINDOW_TYPE_HANNING; // hanning window by default
	m_winSize = winSize;
	calculate_window();
}

WindowFunction::WindowFunction(int winSize, WindowType winType) {
	m_winType = winType;
	m_winSize = winSize;
	calculate_window();
}

WindowFunction::~WindowFunction() {
	free(m_window);
}

// getters and setters

void WindowFunction::set_winType(WindowType winType) {
	m_winType = WindowType(winType);
}

WindowType WindowFunction::get_winType() {
	return m_winType;
}

void WindowFunction::set_winSize(int winSize){
	m_winSize = winSize;
}

int WindowFunction::get_winSize(){
	return m_winSize;
}

SAMPLE* WindowFunction::get_window(){
	return m_window;
}

void WindowFunction::calculate_window() {
	// memory allocaiton
	int winSize = this->get_winSize();
	m_window = (SAMPLE*)malloc(sizeof(SAMPLE)*winSize);

	int m = winSize / 2;
	SAMPLE r;

	switch (m_winType) {
	case WINDOW_TYPE_BARTLETT: // Bartlett (triangular) window
		for (int n = 0; n < winSize; n++)
			m_window[n] = 1.0 - (double)(std::abs(n - m)) / (double)m;
		break;

	case WINDOW_TYPE_HANNING: // Hann window
		r = M_PI / (m + 1);
		for (int n = -m; n < m; n++)
			m_window[m + n] = 0.5 + 0.5 * cos(n * r);
		break;

	case WINDOW_TYPE_HAMMING: // Hamming window
		r = M_PI / m;
		for (int n = -m; n < m; n++)
			m_window[m + n] = 0.54 + 0.46 * cos(n * r);
		break;

	case WINDOW_TYPE_BLACKMAN: // Blackman window
		r = M_PI / m;
		for (int n = -m; n < m; n++)
			m_window[m + n] = 0.42 + 0.5 * cos(n * r) + 0.08 * cos(2 * n * r);
		break;

	default: // Rectangular window function
		for (int n = 0; n < winSize; n++)
			m_window[n] = 1.0;
		break;
	}
}

///////////////////////////////////////////////////////////////////////////
class FFT {
public:
	static std::vector<std::complex<SAMPLE> > fft(std::vector<std::complex<SAMPLE> > x);
};

std::vector<std::complex<SAMPLE> > FFT::fft(std::vector<std::complex<SAMPLE> > x) {
	int N = x.size();

	// base case
	if (N == 1) return x;

	// radix 2 Cooley-Tukey FFT
	// TODO: Must throw
	if (N % 2 != 0) { return std::vector<std::complex<SAMPLE> >(); }

	// fft of even terms
	std::vector<std::complex<SAMPLE> > even(N / 2);
	for (int k = 0; k < N / 2; k++) {
		even[k] = x[2 * k];
	}
	std::vector<std::complex<SAMPLE> > q = fft(even);

	// fft of odd terms
	std::vector<std::complex<SAMPLE> > odd = even;  // reuse the array
	for (int k = 0; k < N / 2; k++) {
		odd[k] = x[2 * k + 1];
	}
	std::vector<std::complex<SAMPLE> > r = fft(odd);

	// combine
	std::vector<std::complex<SAMPLE> > y(N);
	for (int k = 0; k < N / 2; k++) {
		SAMPLE kth = -2.0 * (SAMPLE)k * M_PI / (SAMPLE)N;
		std::complex<SAMPLE> wk = std::complex<SAMPLE>(cos(kth), sin(kth));
		y[k] = q[k] + wk*r[k];
		y[k + N / 2] = q[k] - wk*r[k];
	}
	return y; // COMMENT: fft output size is just half the size, not half +1
}




class FeatureSpectralCentroid
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

	/////////////////////////////////////

	WindowType m_winType;
	SAMPLE m_fBinSize;
	SAMPLE** m_magSpec;

public:

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
	SAMPLE**		get_feature();
	virtual void	calculate_feature();


	/////////////////////////////////////

	FeatureSpectralCentroid(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize, WindowType winType);
	~FeatureSpectralCentroid();

	WindowType get_winType();
	void set_winType(WindowType winType);

	SAMPLE get_fBinSize();
	void calculate_fBinSize();

	SAMPLE** get_magSpec();
	void calculate_magSpec();
};


FeatureSpectralCentroid::FeatureSpectralCentroid(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize, WindowType winType){
	set_signal(signal);
	set_bufSize(bufSize);
	set_fs(fs);
	set_winSize(winSize);
	set_hopSize(hopSize);
	set_winType(winType);
	calculate_fBinSize();
	calculate_magSpec();
}


FeatureSpectralCentroid::~FeatureSpectralCentroid(){
	int winSize = this->get_winSize();
	int nCols = this->get_nCols();

	if (m_signal != NULL){
		free(m_signal);
	}

	if (m_feature != NULL){
		for (int i = 0; i < nCols; ++i){
			free(m_feature[i]);
		}
	}

	if (m_magSpec != NULL){
		for (int i = 0; i < winSize / 2 + 1; ++i){
			free(m_magSpec[i]);
		}
	}
}

WindowType FeatureSpectralCentroid::get_winType(){
	return m_winType; // refer to WindowFunction.h for detailed info on Windows
}

void FeatureSpectralCentroid::set_winType(WindowType winType){
	this->m_winType = winType;
}

SAMPLE FeatureSpectralCentroid::get_fBinSize(){
	return m_fBinSize;
}

void FeatureSpectralCentroid::calculate_fBinSize(){
	int fs = this->get_fs();
	int winSize = this->get_winSize();
	m_fBinSize = (fs / 2) / winSize;
}

SAMPLE** FeatureSpectralCentroid::get_magSpec(){
	return m_magSpec;
}

void FeatureSpectralCentroid::calculate_magSpec(){
	// bring in necessary variables
	SAMPLE* signal = this->get_signal();
	int bufSize = this->get_bufSize();
	int hopSize = this->get_hopSize();
	int winSize = this->get_winSize();
	WindowType winType = this->get_winType();
	set_nRows(ceil(bufSize/(double)hopSize));
	int nRows = this->get_nRows();

	int nFFTCols = (winSize / 2) + 1;
	
	std::cout << "Variables declared" << std::endl;

	// get window; TODO: get this elsewhere?
	SAMPLE* window; // Q: const value?
	WindowFunction* winObj = new WindowFunction(winSize, WINDOW_TYPE_HANNING);
	window = winObj->get_window();

	std::cout << "Window declared" << std::endl;

	// memory allocation for m_magSpec (vertical time axis and horizontal window)
	this->m_magSpec = (SAMPLE**)malloc(nFFTCols*sizeof(SAMPLE*));
	for (int i = 0; i < nFFTCols; ++i){
		m_magSpec[i] = (SAMPLE*)malloc(nRows * sizeof(SAMPLE));
	}

	std::vector<std::complex<double> > complexIn(winSize);
	std::vector<std::complex<double> > fftOut;

	// store double array as complex data type to conform with the FFT algorithm used here
	for (int i = 0; i < nRows; i++){
		for (int j = 0; j < winSize; j++){
			if (i*hopSize + j < bufSize){
				complexIn[j] = std::complex<SAMPLE>(signal[i*hopSize + j] * window[j], 0.0);
			}
			else{ //zero-padding
				complexIn[j] = std::complex<SAMPLE>(0 * window[j], 0.0);
			}
		}
		fftOut = FFT::fft(complexIn);
		for (int j = 0; j < nFFTCols; j++){
			m_magSpec[i][j] = abs(fftOut[i]);
		}
	}
	std::cout << "val1	" << m_magSpec[0][0] << std::endl;
	std::cout << "val2	" << m_magSpec[0][nFFTCols-1] << std::endl;
	std::cout << "val3	" << m_magSpec[nRows-1][0] << std::endl;
	std::cout << "val4	" << m_magSpec[nRows - 1][nFFTCols - 1] << std::endl;
}


void FeatureSpectralCentroid::calculate_feature(){

	int fs = this->get_fs();
	SAMPLE* signal = this->get_signal();
	int bufSize = this->get_bufSize();
	int winSize = this->get_winSize();
	int hopSize = this->get_hopSize();
	SAMPLE fBinSize = this->get_fBinSize();

	// set and get nCols and nRows
	set_nCols(1);
	set_nRows(ceil(bufSize / hopSize);
	int nCols = get_nCols();
	int nRows = get_nRows();

	// allocate memory for feature
	this->m_feature = (SAMPLE**)malloc(nCols*sizeof(SAMPLE*));
	for (int i = 0; i < nCols; ++i){
		m_feature[i] = (SAMPLE*)malloc(nRows*sizeof(SAMPLE*));
	}

	// get magnitude spectrum
	SAMPLE** magSpec = this->get_magSpec();
	SAMPLE* oneRow;
	int maxIdx;
	for (int i = 0; i < nRows; i++){
		// take one entire row and its value
		oneRow = m_feature[i];
		int rowLen = sizeof(oneRow)/ sizeof(SAMPLE);
		SAMPLE maxVal = *std::max_element(oneRow, oneRow + rowLen);

		// compute the distance
		maxIdx = *std::distance(oneRow, maxVal);
		
		// get the freq value
		m_feature[i][0] = maxIdx*fBinSize;
	}
}







/////////////////////////////////////////////////////////



SAMPLE* FeatureSpectralCentroid::get_signal(){
	if (this->m_signal == NULL){
		printf("m_signal is null\n");
		exit(1);
	}
	else{
		return this->m_signal;
	}
}

void FeatureSpectralCentroid::set_signal(SAMPLE* signal){
	if (signal == NULL){
		printf("input signal is null\n");
		return;
	}
	else{
		int bufSize = get_bufSize();
		this->m_signal = (SAMPLE*)malloc(sizeof(SAMPLE)*bufSize);
		this->m_signal = signal;
	}
}



int FeatureSpectralCentroid::get_bufSize(){
	return this->m_bufSize;
}

void FeatureSpectralCentroid::set_bufSize(int bufSize){
	this->m_bufSize = bufSize;
}

int FeatureSpectralCentroid::get_fs(){
	return this->m_fs;
}

void FeatureSpectralCentroid::set_fs(int fs){
	this->m_fs = fs;
}

int FeatureSpectralCentroid::get_winSize(){
	return this->m_winSize;
}

void FeatureSpectralCentroid::set_winSize(int winSize){
	this->m_winSize = winSize;
}

int FeatureSpectralCentroid::get_hopSize(){
	return this->m_hopSize;
}

void FeatureSpectralCentroid::set_hopSize(int hopSize){
	this->m_hopSize = hopSize;
}

// feature computation

int FeatureSpectralCentroid::get_nRows(){
	return this->m_nRows;
}

void FeatureSpectralCentroid::set_nRows(int nRows){
	this->m_nRows = nRows;
}

int FeatureSpectralCentroid::get_nCols(){
	return this->m_nCols;
}

void FeatureSpectralCentroid::set_nCols(int nCols){
	this->m_nCols = nCols;
}


SAMPLE** FeatureSpectralCentroid::get_feature(){
	return this->m_feature;
}

////////////////////////////////////////////////////

void FeatureSpectralCentroid::calculate_feature(){
	return;
}


int main(){

	SAMPLE signal[44100];
	int	bufSize = 44100;
	int const winSize = 1024;
	int	hopSize = 1023;
	int fs = 44100;
	for (int i = 0; i < fs; ++i){
		signal[i] = ((double)rand() / (RAND_MAX)) * 2 - 1;
	}

	int nRows = ceil(bufSize / (double)hopSize);
	WindowType winType = WINDOW_TYPE_HANNING;
	
	std::cout << signal[100] << std::endl;
	std::cout << signal[1000] << std::endl;
	std::cout << signal[10000] << std::endl;

	// get_mag test //////////////////////////////////////////////////////
	/*
	int nFFTCols = (winSize / 2) + 1;
	SAMPLE* window; // Q: const value?
	WindowFunction* winObj = new WindowFunction(winSize, WINDOW_TYPE_HANNING);
	window = winObj->get_window();
	// get bufSize

	std::cout << "window created" << std::endl;

	// memory allocation for m_magSpec;
	
	SAMPLE** m_magSpec = (SAMPLE**)malloc(nFFTCols*sizeof(SAMPLE*));
	for (int i = 0; i < nFFTCols; ++i){
		m_magSpec[i] = (SAMPLE*)malloc(nRows * sizeof(SAMPLE));
	}

	for (int i = 0; i < nRows; ++i){
		for (int j = 0; j < nFFTCols; ++j){
			m_magSpec[i][j] = 0;
		}
	}

	std::vector<std::complex<double> > complexIn(winSize);
	std::vector<std::complex<double> > fftOut;

	// store float array as complex data type to conform with the FFT algorithm used here
	for (int i = 0; i < nRows; i++){
		for (int j = 0; j < winSize; j++){
			if (i*hopSize + j < bufSize){
				complexIn[j] = std::complex<SAMPLE>(signal[i*hopSize + j] * window[j], 0.0);
			}
			else{ //zero-padding
				complexIn[j] = std::complex<SAMPLE>(0 * window[j], 0.0);
			}
		}
		fftOut = FFT::fft(complexIn);
		for (int j = 0; j < nFFTCols; j++){
			m_magSpec[i][j] = abs(fftOut[i]);
		}
	}
	
	std::cout << m_magSpec[nRows/2][nFFTCols/2] << std::endl;

	////////////////////////////////////////////////////////////////
	*/

	// test spec

	FeatureSpectralCentroid* testObj = new FeatureSpectralCentroid(signal, bufSize, fs, winSize, hopSize, winType);

	std::cout << "object created" << std::endl;

	SAMPLE* sig2 = testObj->get_signal();
	std::cout << "Obj sig1	:" << sig2[100] << std::endl;
	std::cout << "Obj sig2	:" << sig2[1000] << std::endl;
	std::cout << "Obj sig3	:" << sig2[10000] << std::endl;
		
	std::cout << "Obj bufSize	:" << testObj->get_bufSize() << std::endl;
	std::cout << "Obj fs		:" << testObj->get_fs() << std::endl;
	std::cout << "Obj winSize	:" << testObj->get_winSize() << std::endl;
	std::cout << "Obj hopSize	:" << testObj->get_hopSize() << std::endl;
	std::cout << "Obj fBinSize	:" << testObj->get_fBinSize() << std::endl;
	std::cout << "Obj winType	:" << testObj->get_winType() << std::endl;
	std::cout << "Obj nRows		:" << testObj->get_nRows() << std::endl;
	std::cout << "Obj nCols		:" << testObj->get_nCols() << std::endl;

	SAMPLE** mag = testObj->get_magSpec();

	std::cout << "mag allocated" << std::endl;

	
	std::cout << "Obj magSpec1	:" << mag[10][20] << std::endl;
	std::cout << "Obj magSpec1	:" << mag[100][200] << std::endl;
	std::cout << "Obj magSpec1	:" << mag[3][512] << std::endl;
	
	std::cout << "val1	" << mag[0][0] << std::endl;
	std::cout << "val2	" << mag[0][testObj->get_winSize()] << std::endl;
	std::cout << "val3	" << mag[testObj->get_nRows()-1][0] << std::endl;
	std::cout << "val4	" << mag[testObj->get_nRows() - 1][testObj->get_winSize()] << std::endl;
	



	return 0;
}

