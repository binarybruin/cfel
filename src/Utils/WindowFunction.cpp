#include "WindowFunction.h"
#include <math.h>
#include <stdlib.h>

using namespace std;

WindowFunction::WindowFunction(int winSize) {
	m_winType = 2; // hanning window by default
	m_win
	m_window = calculate_window();
	
}

WindowFunction::WindowFunction(WindowType winType, int winType) {
	if (wintType > NUM_WINDOW_TYPES
	m_winType = winType;
	
	
}

WindowFunction::WindowFunction() {

}


void WindowFunction::setWindowType(int winType) {
	m_winType = WindowType(winType);
}

int WindowFunction::getWindowType() const {
	return int(m_winType);
}

SAMPLE* WindowFunction::calculate_window() {
	int m = m_winSize / 2;

	switch (m_winType) {
	case WINDOW_TYPE_BARTLETT: // Bartlett (triangular) window
			for (int n = 0; n < m_winSize; n++)
					w[n] = 1.0 - fabs(n - m) / m;
			break;

	case WINDOW_TYPE_HANNING: // Hann window
			r = M_PI / (m + 1);
			for (int n = -m; n < m; n++)
					w[m + n] = 0.5 + 0.5 * cos(n * r);
			break;

	case WINDOW_TYPE_HAMMING: // Hamming window
			r = M_PI / m;
			for (int n = -m; n < m; n++)
					w[m + n] = 0.54 + 0.46 * cos(n * r);
			break;

	case WINDOW_TYPE_BLACKMAN: // Blackman window
			r = M_PI / m;
			for (int n = -m; n < m; n++)
					w[m + n] = 0.42 + 0.5 * cos(n * r) + 0.08 * cos(2 * n * r);
			break;

	default: // Rectangular window function
			for (int n = 0; n < m_winSize; n++)
					w[n] = 1.0;
			break;
	}

	return w;
}
}
