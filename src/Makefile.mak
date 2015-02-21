TARGET = FeatureController.o
OBJS = FeatureController.o FeatureRMS.o FeatureStatistics.o FeatureExtraction.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

test : $(TARGET)
        $(CC) $(LFLAGS) $(OBJS) -o test

FeatureController.o : FeatureController.h FeatureController.cpp FeatureExtraction.h FeatureExtraction.cpp FeatureStatistics.h FeatureStatistics.cpp FeatureClasses/FeatureRMS.h FeatureClasses/FeatureRMS.cpp
        $(CC) $(CFLAGS) FeatureController.cpp

FeatureRMS.o : FeatureClasses/FeatureRMS.h FeatureClasses/FeatureRMS.cpp
        $(CC) $(CFLAGS) FeatureRMS.cpp

FeatureStatistics.o : FeatureStatistics.h FeatureStatistics.cpp FeatureExtraction.h FeatureExtraction.cpp
        $(CC) $(CFLAGS) FeatureStatistics.cpp

FeatureExtraction.o : FeatureExtraction.h FeatureExtraction.cpp
        $(CC) $(CFLAGS) FeatureExtraction.cpp



clean :
        \rm *.o *~ test