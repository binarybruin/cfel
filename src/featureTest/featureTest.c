//#include <FeatureController.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// the buffer will be 100*(BUFFER_SIZE) like in JUCE
#define BUFFER_SIZE         1024
#define FREQUENCY           440
#define SAMPLING_RATE       44100
#define PI                  3.1415

    int i,j;
    typedef float SAMPLE;
    float sineBuf[BUFFER_SIZE*100];
    float RMSBuf[BUFFER_SIZE*100]; // is this the correct size ?
    char sineFile[] = "featureTest.txt";
    char RMSFile[] = "RMSTest.txt";
    //char ZCRFile[] = "ZCRTest.txt";

    void featureRMSTest(float buffer[BUFFER_SIZE*100], char fTestfilename[], FILE* fileptr);
    //void featureZCRTest(float buffer[BUFFER_SIZE*100], char fTestfilename[], FILE* fileptr);

int main(){

 
    // try to open output file
  FILE * sineptr = fopen(sineFile, "w");
  if (sineptr == NULL) {
    printf("Could not open %s for writing.\n", sineFile);
    return EXIT_FAILURE;
  }

  // try to open RMS output file
  FILE * rmsptr = fopen(RMSFile, "w");
  if (rmsptr == NULL) {
    printf("Could not open %s for writing.\n", RMSFile);
    return EXIT_FAILURE;
  }

   // try to open ZCR output file
  //FILE * zcrptr = fopen(ZCRFile, "w");
 // if (zcrptr == NULL) {
  //  printf("Could not open %s for writing.\n", ZCRFile);
 //   return EXIT_FAILURE;
 // }


    // sine wave parameters:
    float sampleSine, phase;
    static float prev_phase = 0;

    for( i = 0; i < BUFFER_SIZE*100; i++){

        //sine synthesis:
        phase = 2 * PI * FREQUENCY/ SAMPLING_RATE + prev_phase;
        sampleSine = sin(phase);
        prev_phase = phase;
        sineBuf[i] = sampleSine;
        fprintf(sineptr, "sineBuf[%d] = %f\n", i, sineBuf[i]);
    }


    //test features
   // featureRMSTest(sineBuf, RMSFile, rmsptr);
    //featureZCRTest(sineBuf, ZCRFile, zcrptr);

    fclose(sineptr);
    fclose(rmsptr);
   // fclose(zcrptr);

    return EXIT_SUCCESS;
}



/*
 * feature function tests  
 */


/* ROOT MEAN SQUARE */
//void featureRMSTest(float buffer[BUFFER_SIZE*100], char fTestfilename[], FILE* fileptr){

/* Parameter initialization */
//int m_bufSize = BUFFER_SIZE*100;
//int m_winSize = m_bufSize/6;
//int m_hopSize = m_winSize/2;
//int m_nRows;
//float **m_feature;
//float *m_signal = buffer;

/* copy and pasted from FeatureRMS.cpp 

            int m_nCols = 1;
            m_nRows = ceil(m_bufSize/(double)m_hopSize);

            // allocate memory for feature
			m_feature = (SAMPLE**)malloc(m_nRows*sizeof(SAMPLE*));
			for (int i = 0; i < m_nCols; ++i){
				m_feature[i] = (SAMPLE*)malloc(m_nCols*sizeof(SAMPLE));
			}
			
			// RMS calculation
			SAMPLE sqrSum;
			SAMPLE val;
			for (int i = 0; i < m_nCols; ++i){			
				for (int j = 0; j < m_nRows; ++j){
					sqrSum = 0.0;
					for (int k = 0; k < m_winSize; ++k){
						if (j*m_hopSize+k >= m_bufSize){ // conceptually zero-padding
							val = 0;
						}
						else{
							val = buffer[j*m_hopSize+k];
						}
						sqrSum += val*val;
					}
					m_feature[i][j] = sqrt(sqrSum/(SAMPLE)m_winSize);
					fprintf(fileptr, "m_feature[%d][%d] = %f\n", j, i, m_feature[i][j]); //ADDED FOR PRINTOUT of m_feature
				}
			}
		}



 ZERO CROSSING RATE */

/*
void featureZCRTest(float buffer[BUFFER_SIZE*100], char fTestfilename[], FILE* fileptr){

 Parameter initialization 
int m_bufSize = BUFFER_SIZE*100;
int m_winSize = m_bufSize/6;
int m_hopSize = m_winSize/2;
int m_nRows;
float **m_feature;
float *m_signal = buffer;

 copy and pasted from FeatureRMS.cpp 

            int m_nCols = 1;
            m_nRows = ceil(m_bufSize/m_hopSize);

            // allocate memory for feature
			m_feature = (SAMPLE**)malloc(m_nCols*sizeof(SAMPLE*)); // CORRECTION: m_feautre -> m_feature
			for (int i = 0; i < m_nCols; ++i){
				m_feature[i] = (SAMPLE*)malloc(m_nRows*sizeof(SAMPLE*));
			}
			
			// ZCR calculation
			if (m_winSize <= 0){ 
				printf("Check your winSize.\n");
				exit(1);
			}
			else if (m_winSize > m_bufSize){
				printf("winSize exceeds bufSize.\n");
				exit(1);
			}
			else{
			int zcc; // zero crossing count
				for (i = 0; i < m_nCols; ++i){			
					for (int j = 0; j < m_nRows; ++j){
						zcc = 0;
						for (int k = 0; k < m_winSize; ++k){
							if (j*m_hopSize+k <= m_nCols){
								// check the sign of two consecutive samples
								if (m_signal[j*m_hopSize+k] < 0 && m_signal[j*m_hopSize+k+1] > 0){
									++zcc;
								}
								if (m_signal[j*m_hopSize+k] > 0 && m_signal[j*m_hopSize+k+1] < 0){
									++zcc;
								}
							}
						}
						m_feature[j][i] = (SAMPLE)zcc/m_winSize;
						fprintf(fileptr, "m_feature[%d][%d] = %f\n", j, i, m_feature[j][i]); //ADDED FOR PRINTOUT of m_feature
					}
				}	 
			}
}*/
