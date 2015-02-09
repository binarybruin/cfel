# compiler type
CC = g++

# Targets and objects
TARGET = test
OBJS = Test.o ???

# compiler flags
CFLAGS = -Wall -c
LFLAGS = -Wall
DEBUG = -g

# the build target executable:
# what is the difference between target executable and .o files 
TARGET = test


$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)
	
	

	
	
	
	
	
clean:
	rm -rf $(OBJECTS) $(TARGET) *.o