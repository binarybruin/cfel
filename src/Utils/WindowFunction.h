#include "../FeatureExtraction.h"

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
		WindowFunction(int winSize, WindowType winType);
		~WindowFunction();
		
		void set_winType(WindowType winType);
	    WindowType get_winType();
				
		void set_winSize(int winSize);
		int get_winSize();
		
		SAMPLE* get_window();
		void calculate_window();
};


