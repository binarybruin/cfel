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
		int m_winSize;
		SAMPLE* m_window;
		
	public:
		WindowFunction(int winSize);
		WindowFunction(WindowType winType, int winSize);
		~WindowFunction();

	    WindowType getWindowType();
		void setWindowType(int winType);

		int get_winSize();
		void set_winSize(int winSize);

		SAMPLE* getWindow();
		SAMPLE* getWindow(int winType);
		void calculate_window();
};


