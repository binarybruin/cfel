#include "EuclidDist.h"
#include <math.h>

namespace FeatureExtraction {
namespace Utils {

double EuclidDist::euclidDist(double* pVec, int nSize) {
	double fSum = 0.0;

	for (int i = 0; i < nSize; i++)
		fSum+= pVec[i]*pVec[i];

	return sqrt(fSum);
}

}
}
