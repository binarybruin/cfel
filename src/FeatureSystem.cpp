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

int bufferSize = 1024;
int fs = 44100;
int winSize = bufferSize;
int hopSize = bufferSize/2;
}

// constructor
FeatureSystem(); 

//getters and setters

int get_bufferSize() {
    return this->m_bufferSize;
}

void set_bufferSize(int bufferSize) { 
    this->m_bufferSize = bufferSize;
}

int get_fs() { 
    return this->m_fs;
}

void set_fs(int fs) {
    this->m_fs = fs;
}

int get_winSize() {
    return this->m_winSize;
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

