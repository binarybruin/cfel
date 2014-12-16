#pragma once

#include "../FeatureExtraction.h"

using namespace std;

namespace FeatureExtraction{
namespace Utils{


class RemoveDC 
{
    private:
        SAMPLE* m_DCremoved;

    public:
	RemoveDC(SAMPLE* buffer, int bufSize);
	~RemoveDC();	

        void calculate_removeDC(SAMPLE* buffer);
	SAMPLE* get_DCremoved();
};

}
}
