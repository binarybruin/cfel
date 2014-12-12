#pragma once

#include <vector>
#include <complex>

using namespace std;

namespace FeatureExtraction {
namespace Utils {

class FFT {
public:
	static vector<complex<double> > fft(vector<complex<double> > x);
};

}
}
