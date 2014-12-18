#include "FeatureController.h"
#include <stdlib.h>
#include <iostream>
#include <string>

int main() {

	SAMPLE signal[44100];
	int	bufSize = 44100;
	int	winSize = 4410;
	int	hopSize = 44090;
	int fs = 44100;
	for (int i = 0; i < fs; ++i){
		signal[i] = ((double)rand() / (RAND_MAX)) * 2 - 1;
	}

	std::cout << signal[100] << std::endl;
	std::cout << signal[1000] << std::endl;
	std::cout << signal[10000] << std::endl;

	FeatureController* controller = new FeatureController(signal, bufSize, fs, winSize, hopSize);

	controller->setFeature();

	FeatureRMS* featureRMS = controller->getRMSFeature();

	int t_bufSize = featureRMS->get_bufSize();
	std::cout << "bufSize: " << t_bufSize << std::endl;
	int t_winSize = featureRMS->get_winSize();
	std::cout << "winSize: " << t_winSize << std::endl;

	featureRMS->set_rows_cols();

	SAMPLE** result_RMS = featureRMS->calculate_feature();

	int nCols = featureRMS->get_nCols();
	int nRows = featureRMS->get_nRows();
	std::cout << "cols: " << nCols << std::endl;
	std::cout << "rows: " << nRows << std::endl;

	for (int i = 0; i < bufSize; i++) {
		//std::cout << featureRMS->get_signal()[i] << std::endl;
	}

	SAMPLE** feature = featureRMS->get_feature();
	for (int i = 0; i < nCols; i++) {
		for (int j = 0; j < nRows; j++) {
			std::cout << feature[j][i] << std::endl;
		}
	}

	char input;
	std::cin >> input;
}