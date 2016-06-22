
CC = g++
CCFLAGS = -O -g -std=c++11 -Wall -pedantic 

all: sort00 sort01

sort00: main00.cpp sort_utils.cpp sort.cpp sort.hpp
	$(CC) $(CCFLAGS) -o sort00 main00.cpp sort_utils.cpp sort.cpp

sort01: main01.cpp sort_utils.cpp sort.cpp sort.hpp
	$(CC) $(CCFLAGS) -o sort01 main01.cpp sort_utils.cpp sort.cpp
