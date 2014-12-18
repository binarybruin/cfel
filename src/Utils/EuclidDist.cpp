#include "EuclidDist.h"
#include <math.h>

SAMPLE EuclidDist::euclidDist(SAMPLE* pVec, int nSize) {

	double fSum = 0.0;

	for (int i = 0; i < nSize; i++)
		fSum+= pVec[i]*pVec[i];

	return (SAMPLE)sqrt(fSum);
}

