//
// FeatureSystem.cpp
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

#include <iostream>
#include "FeatureSystem.h"

using namespace FeatureSystem;

void initParams()
{
//these parameters will eventually come from the codec, or user definition.

	m_bufSize = 1024;
	m_fs = 44100;
	m_winSize = bufSize;
	m_hopSize = bufSize/2;
}

// constructor
FeatureSystem(); 

//getters and setters

int get_bufSize() {
    return m_bufSize;
}

void set_bufSize(int bufSize) { 
    m_bufSize = bufSize;
}

int get_fs() { 
    return m_fs;
}

void set_fs(int fs) {
    m_fs = fs;
}

int get_winSize() {
    return m_winSize;
}

void set_winSize(int winSize) {
    this->m_winSize = winSize;
}

int get_hopSize() { 
    return this->m_hopsize;
}

void set_hopSize(int hopSize) {
    this->m_hopSize = hopSize;
}

