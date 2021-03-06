#include "WindowFunction.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

// Constructors/destructors
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
					m_window[n] = 1.0 - (double)(std::abs(n - m)) /(double)m;
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
