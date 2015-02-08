# compiler type
CC = g++

# compiler flags

CFLAGS = -Wall -g
LDFLAGS = -lm

# the build target executable:
# what is the difference between target executable and .o files 
TARGET = test

test.o: test.cpp 
	$(CC) $(LDFLAGS) test.cpp

all: test.o
	$(CC) $(CFLAGES) test.o $(LDFLAGS) -o test
	
clean:
	rm -rf $(OBJECTS) $(TARGET) *.o