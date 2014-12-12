#include "FFT.h"
#include <math.h>

using namespace std;

namespace FeatureExtraction {
namespace Utils {

// compute the FFT of x, assuming its length is a power of 2
vector<complex<double> > FFT::fft(vector<complex<double> > x) {
	int N = x.size();

	// base case
	if (N == 1) return x;

	// radix 2 Cooley-Tukey FFT
	// TODO: Must throw
	if (N % 2 != 0) { return vector<complex<double> >(); }

	// fft of even terms
	vector<complex<double> > even(N/2);
	for (int k = 0; k < N/2; k++) {
		even[k] = x[2*k];
	}
	vector<complex<double> > q = fft(even);

	// fft of odd terms
	vector<complex<double> > odd = even;  // reuse the array
	for (int k = 0; k < N/2; k++) {
		odd[k] = x[2*k + 1];
	}
	vector<complex<double> > r = fft(odd);

	// combine
	vector<complex<double> > y(N);
	for (int k = 0; k < N/2; k++) {
		double kth = -2.0 * (double)k * M_PI / (double)N;
		complex<double> wk = complex<double>(cos(kth), sin(kth));
		y[k]       = q[k] + wk*r[k];
		y[k + N/2] = q[k] - wk*r[k];
	}
	return y;
}

}
}
