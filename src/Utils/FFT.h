#pragma once

#include <vector>
#include <complex>

#include "../FeatureExtraction.h"

using namespace std;

class FFT {
public:
	static vector<complex<SAMPLE> > fft(vector<complex<SAMPLE> > x);
};
