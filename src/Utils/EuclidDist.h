#pragma once

#include "../FeatureExtraction.h"

namespace FeatureExtraction {
namespace Utils {

class EuclidDist {
public:
	static SAMPLE euclidDist(SAMPLE* pVec, int nSize);
};

}
}
