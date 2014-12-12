#pragma once

#include "FeatureExtraction.h"

enum WindowType {
	WINDOW_TYPE_RECTANGULAR = 0,
	WINDOW_TYPE_BARTLETT,
	WINDOW_TYPE_HANNING,
	WINDOW_TYPE_HAMMING,
	WINDOW_TYPE_BLACKMAN,
	NUM_WINDOW_TYPES
};

class WindowFunction {
	private:
		WindowType m_winType;
		SAMPLE* m_window
		
		
	public:
		WindowFunction();
		WindowFunction(int winType);
		~WindowFunction();
				
		int getWindowType();
		void setWindowType(int winType);
};


