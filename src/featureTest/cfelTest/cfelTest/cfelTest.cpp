
#pragma once
#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <complex>
#include <stdlib.h>

#define _USE_MATH_DEFINES
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
	void calculate_window();
}

WindowFunction::WindowFunction(int winSize, WindowType winType) {
	m_winType = winType;
	m_winSize = winSize;
	void calculate_window();
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
	int m = m_winSize / 2;
	SAMPLE r;

	switch (m_winType) {
	case WINDOW_TYPE_BARTLETT: // Bartlett (triangular) window
		for (int n = 0; n < m_winSize; n++)
			m_window[n] = 1.0 - (double)(std::abs(n - m))/(double) m;
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
		for (int n = 0; n < m_winSize; n++)
			m_window[n] = 1.0;
		break;
	}
}

class FFT {
public:
	static std::vector<std::complex<SAMPLE> > fft(std::vector<std::complex<SAMPLE> > x);
};

// compute the FFT of x, assuming its length is a power of 2
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
	return y;
}


class FeatureExtractionSpectral
{

private:
	//FeatureExtraction
	SAMPLE*			m_signal;
	int				m_bufSize;
	int				m_fs;
	int				m_winSize;
	int				m_hopSize;

	SAMPLE**		m_feature;
	int				m_nRows;
	int				m_nCols;

	//FeatureExtractionSpectral
	int m_winType;
	SAMPLE m_fBinSize;
	SAMPLE** m_magSpec;

public:

	FeatureExtractionSpectral(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize);
	~FeatureExtractionSpectral();

	int get_winType();
	void set_winType(int winType);

	SAMPLE get_fBinSize();
	void calculate_fBinSize();

	SAMPLE** get_magSpec();
	void calculate_magSpec();

	//FeatureExtraction
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

	virtual void	preprocess();

	SAMPLE**		get_feature();
	virtual void	calculate_feature();
	int				get_nRows();
	int				get_nCols();

};

FeatureExtractionSpectral::FeatureExtractionSpectral(SAMPLE* signal, int bufSize, int fs, int winSize, int hopSize){
	set_signal(signal);
	set_bufSize(bufSize);
	set_fs(fs);
	set_winSize(winSize);
	set_hopSize(hopSize);
	calculate_fBinSize();
	calculate_magSpec();
}

FeatureExtractionSpectral::~FeatureExtractionSpectral(){
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


int FeatureExtractionSpectral::get_winType(){
	return m_winType; // refer to WindowFunction.h for detailed info on Windows
}

void FeatureExtractionSpectral::set_winType(int winType){
	m_winType = winType;
}

SAMPLE FeatureExtractionSpectral::get_fBinSize(){
	return m_fBinSize;
}

void FeatureExtractionSpectral::calculate_fBinSize(){
	int fs = this->get_fs();
	int winSize = this->get_winSize();
	m_fBinSize = (fs / 2) / winSize;
}


SAMPLE** FeatureExtractionSpectral::get_magSpec(){
	return m_magSpec;
}

void FeatureExtractionSpectral::calculate_magSpec(){
	int hopSize = this->get_hopSize();
	int winSize = this->get_winSize();
	int nRows = this->get_nRows(); // vertical time axis

	// memory allocation for m_magSpec;
	m_magSpec = (SAMPLE**)malloc(winSize*sizeof(SAMPLE*));
	for (int i = 0; i < winSize / 2 + 1; ++i){
		m_magSpec[i] = (SAMPLE*)malloc(nRows*sizeof(SAMPLE*));
	}

	// get buffer
	SAMPLE* signal = this->get_signal();

	// get window
	WindowFunction* windowObj = new WindowFunction(winSize);
	SAMPLE* window = windowObj->get_window();
	//SAMPLE* winSig = (SAMPLE*)malloc(winSize*sizeof(SAMPLE)); 
	std::vector<std::complex<SAMPLE>>winSig; // windowed sig

	// get the magnitude spectrum

	for (int i = 0; i < nRows; ++i){

		// hopping (happens in buffer) and windowing
		for (int j = 0; j < winSize; ++j){
			winSig[j] = signal[i*hopSize + j] * window[j];
		}
		std::vector<std::complex<SAMPLE>> fftOut;
		fftOut = FFT::fft(winSig);

		// put the fftout to m_magSpec
		for (int j = 0; j < winSize / 2 + 1; ++j){
			m_magSpec[i][j] = (SAMPLE)abs(fftOut[i]);
		}
	}
}

int main()
{
	std::cout << "yo!!\n";

	return 0;
}




