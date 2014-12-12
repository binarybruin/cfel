#include "WindowFunction.h"
#include <math.h>
#include <stdlib.h>

using namespace std;

WindowFunction::WindowFunction(int winType) {
	m_iWindowType = WindowType(iWindowType);
}

void WindowFunction::setWindowType(int iWindowType) {
	m_iWindowType = WindowType(iWindowType);
}

int WindowFunction::getWindowType() const {
	return int(m_iWindowType);
}

vector<double> WindowFunction::generate(int nSamples) const {
	// generate nSamples window function values
	// for index values 0 .. nSamples - 1
	int m = nSamples / 2;
	double r;
	vector<double> w(nSamples);

	switch (m_iWindowType) {
	case WINDOW_TYPE_BARTLETT: // Bartlett (triangular) window
			for (int n = 0; n < nSamples; n++)
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
		// TODO: Actually we should throw exception here
			for (int n = 0; n < nSamples; n++)
					w[n] = 1.0;
			break;
	}

	return w;
}
}
