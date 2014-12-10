//
// FeatureSystem.h
//
// =================================================================== //
//
// Citygram system information class
//
// =================================================================== //
//
// Created by Michelle Auyoung, Jordan Juras, Jaeseong You
// New York University 12/8/14
// C Programming, Fall 2014
//
// =================================================================== //

#ifndef __CFEL__FeatureSystem__
#define __CFEL__FeatureSystem__

#include <stdio.h>
#include <math.h>

class FeatureSystem {
	private:
		float*			m_signal;
		int				m_bufferSize;
		int				m_fs;
		int				m_winSize;
		int				m_hopSize;

	public:
		FeatureSystem();
        
        //void            initParams() : 
		float*			get_signal();
		void			set_signal(float* signal);
		int				get_bufferSize();
		void			set_bufferSize(int bufferSize);
		int				get_fs();
		void			set_fs(int fs);
		int				get_winSize();
		void			set_winSize(int winSize);
		int				get_hopSize();
		void			set_hopSize(int hopSize);
};

#endif
