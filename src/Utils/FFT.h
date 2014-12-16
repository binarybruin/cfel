#pragma once

#include <vector>
#include <complex>

#include "../FeatureExtraction.h"

using namespace std;

namespace FeatureExtraction {
namespace Utils {

class FFT {
public:
	static vector<complex<SAMPLE> > fft(vector<complex<SAMPLE> > x);
};

}
}
