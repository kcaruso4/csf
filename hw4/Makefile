
CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -g

#Creates the target executable for the first part of the homework
csim: main.o argsHandlingFunctions.o cache.o cBlock.o cSet.o
	$(CC) -o csim main.o argsHandlingFunctions.o cache.o cBlock.o cSet.o

#Compiles CTreeTest.cpp to create CTreeTest.o
main.o: main.cpp argsHandlingFunctions.h cBlock.h cSet.h cache.h
	$(CC) $(CFLAGS) -c main.cpp

argsHandlingFunctions.o: argsHandlingFunctions.cpp argsHandlingFunctions.h
	$(CC) $(CFLAGS) -c argsHandlingFunctions.cpp

cache.o: cache.cpp cache.h cSet.h
	$(CC) $(CFLAGS) -c cache.cpp

cBlock.o: cBlock.cpp cBlock.h
	$(CC) $(CFLAGS) -c cBlock.cpp

cSet.o: cSet.cpp cSet.h cBlock.h
	$(CC) $(CFLAGS) -c cSet.cpp

#Removes all the object files and the executable named csim
clean:
	rm -rf *.o csim
