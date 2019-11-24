#ifndef ARGSHANDLINGFUNCTIONS_H
#define ARGSHANDLINGFUNCTIONS_H
#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <stdlib.h>
#include <math.h>


// This function calculates the power that two must be raised to to equal
// the parameter value. If the power is an integer it is returned. If not
// the parameter value is invalid and an error has occured (return -1)
int getPowerTwo(int val);


// Returns the integer value of a char* passed in. If the parameter
// cannot be converted an error has occured and retunr -1;
int makeInt(char* src);


// This function checks how the cache handles a miss during a store. If
// write-allocate or no-write-allocate return 0 or 1. If nither are passed
// in return -1 because the parameter is invalid.
int checkStoreMiss(char* val);

// This function checks how the cache handles a miss during a store. If
// write-through or write-back returns 0 or 1. If neither then returns -1
// because the parameter is invalid.
int checkStoreWrite(char* val);

// This function checks how the cache will evit any blocks when necessary
// If lru or fifo returns 0 or 1, else returns -1 because the parameter is
// invalid.
int checkEvict(char* val);

// This function returns the index of the set associated with the trace command
std::string getTraceIndex(int index_size, int tag_size, unsigned int address);

//This function returns the index of the tag associated with the trace command
std::string getTraceTag(int tag_size, unsigned int address);

//This function prints the information collected about the trace with respect
//to the cache's functionality.
void printState(int load_hits, int load_misses, int store_hits, int store_misses, int tot_cycles);






#endif
