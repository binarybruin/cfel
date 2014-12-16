/*
 * =====================================================================================
 *
 *       Filename:  testFFT.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/15/2014 07:10:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jaeseong You (), jaeseongyou@gmail.com
 *   Organization:  New York University
 *
 * =====================================================================================
 */


#include "FeatureClasses/FeatureSpectralCentroid.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main(){
    std::cout << "Hello world\n";

    int numSamp = 44100;
    SAMPLE demoSig[numSamp];

    for (int i = 0; i < numSamp; ++i){
        double d = (double)rand()/RAND_MAX;
        demoSig[i] = -1 + d*2;
    }

   std::cout << demoSig[100] << "\n";
   std::cout << demoSig[1000] << "\n";

}
