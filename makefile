# Makefile for CampusGPS
CXX = clang++
CXXFLAGS = -Wall -g

OBJS = main.o campus.o 

TARGET = CampusGPS 

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	
main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp 
	
campus.o: campus.cpp
	$(CXX) $(CXXFLAGS) -c campus.cpp

clean:
	@rm -f $(TARGET) $(OBJS) *.core
