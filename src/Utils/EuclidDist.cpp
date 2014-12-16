#include "EuclidDist.h"
#include <math.h>

namespace FeatureExtraction {
namespace Utils {

<<<<<<< HEAD
	SAMPLE EuclidDist::euclidDist(SAMPLE* pVec, int nSize) {
=======
double EuclidDist::euclidDist(double* pVec, int nSize) {
>>>>>>> 1c1f6c4c216f142add73ba11e9703fa576998778
	double fSum = 0.0;

	for (int i = 0; i < nSize; i++)
		fSum+= pVec[i]*pVec[i];

<<<<<<< HEAD
	return (SAMPLE)sqrt(fSum);
=======
	return sqrt(fSum);
>>>>>>> 1c1f6c4c216f142add73ba11e9703fa576998778
}

}
}
