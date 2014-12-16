#include "RemoveDC.h"
#include <math.h>

namespace FeatureExtraction{
namespace Utils{


RemoveDC::RemoveDC(SAMPLE* buffer, int bufSize){
	calculate_removeDC(SAMPLE* buffer, int bufSize)
}

RemoveDC::~RemoveDC(){
	free(m_DCremoved);
}

void RemoveDC::calculate_removeDC(SAMPLE* buffer, int bufSize){
	//memory allocation
	m_DCremoved = (SAMPLE*)malloc(sizeof(SAMPLE)*bufSize));

	double fSum = 0.0;
	for (int i = 0; i < bufSize; ++i)
		fSum += buffer[i];

	double dc = fSum/bufSize;
	for (int i = 0; i < bufSize; ++i)
		m_DCremoved[i] = buffer[i]-dc; 
}

SAMPLE* RemoveDC::get_DCremoved(){
	return m_DCremoved;
}

}
}
