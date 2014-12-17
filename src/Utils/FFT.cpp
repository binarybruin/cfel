#include "FFT.h"
#include <math.h>

using namespace std;

namespace FeatureExtraction {
namespace Utils {

// compute the FFT of x, assuming its length is a power of 2
vector<complex<SAMPLE> > FFT::fft(vector<complex<SAMPLE> > x) {
	int N = x.size();

	// base case
	if (N == 1) return x;

	// radix 2 Cooley-Tukey FFT
	// TODO: Must throw
	if (N % 2 != 0) { return vector<complex<SAMPLE> >(); }

	// fft of even terms
	vector<complex<SAMPLE> > even(N / 2);
	for (int k = 0; k < N/2; k++) {
		even[k] = x[2*k];
	}
	vector<complex<SAMPLE> > q = fft(even);

	// fft of odd terms
	vector<complex<SAMPLE> > odd = even;  // reuse the array
	for (int k = 0; k < N/2; k++) {
		odd[k] = x[2*k + 1];
	}
	vector<complex<SAMPLE> > r = fft(odd);

	// combine
	vector<complex<SAMPLE> > y(N);
	for (int k = 0; k < N/2; k++) {
		SAMPLE kth = -2.0 * (SAMPLE)k * M_PI / (SAMPLE)N;
		complex<SAMPLE> wk = complex<SAMPLE>(cos(kth), sin(kth));
		y[k]       = q[k] + wk*r[k];
		y[k + N/2] = q[k] - wk*r[k];
	}
	return y; // COMMENT: fft output size is just half the size, not half +1
}

}
}
