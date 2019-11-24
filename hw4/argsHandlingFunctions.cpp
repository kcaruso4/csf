#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <bitset>
#include "argsHandlingFunctions.h"

#define M 32

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::invalid_argument;
using std::out_of_range;
using std::stoi;
using std::bitset;


/*
* Returns the power of two x such that 2^x = val
**/
int getPowerTwo(int val) {
    int exp = (int) (log(val) / log(2));
    if (pow(2, exp) == val) {
        return exp;
    }
    else {
        cerr << "Numeric arguments must be a power of 2" << endl;
        return -1;
    }

}

/*
* Checks the string values can be converted to ints
**/
int makeInt(char* src) {
    std::string s_src = src;
    int value = -1;
    try {
        value = stoi(s_src);
    }
    catch(invalid_argument& e) {
        cerr << "Invalid numberic arugment" << endl;
        return -1;
    }
    catch(out_of_range& e) {
        cerr << "Numberic value out of range" << endl;
        return -1;
    }
    value = stoi(s_src);
    if (value <= 0) {
        cerr << "Numeric argument must be greater than 0" << endl;
        return -1;
    }
    return 0;
}

/*
* Checks how the chache handles a miss during a store. Returns -1 if
* the value is invalide, return 0 if a write-allocate, and a 1 if
* no-write-allocate.
**/
int checkStoreMiss(char* val) {
    std::string s_val = val;
    if (s_val.compare("write-allocate") == 0) {
        return 0;
    }
    else if (s_val.compare("no-write-allocate") == 0) {
        return 1;
    }
    else {
        cerr << "Invalide parameter for determining cache miss functionality on a store" << endl;
        return -1;
    }
}

/*
* Checks whether the cache always writes to memory immediately. If
* the value is invalid return -1, else return 0 if write-through
* or return 1 if write-back and return 0.
**/
int checkStoreWrite(char* val) {
    std::string s_val = val;
    if (s_val.compare("write-through") == 0) {
        return 0;
    }
    else if (s_val.compare("write-back") == 0) {
        return 1;
    }
    else {
        cerr << "Invalide parameter for determining when the cache writes to memory" << endl;
        return -1;
    }
}

/*
* Check to see how the cache evicts blocks when necessary
**/
int checkEvict(char* val) {
    string s_val = val;
    if (s_val.compare("lru") == 0) {
        return 0;
    }
    else if (s_val.compare("fifo") == 0) {
        return 1;
    }
    else {
        cerr << "Invalid parameter for evicting blocks of memory" << endl;
        return -1;
    }
}

//This function returns the index of the set associated with the trace command as a string
std::string getTraceIndex(int index_size, int tag_size, unsigned int address) {
    bitset<M> bit_address(address);
    string index = bit_address.to_string();
    return index.substr(tag_size, index_size);
}

//This function returns the tag of the block associated with the trace command as a string
std::string getTraceTag(int tag_size, unsigned int address) {
    bitset<M> bit_tag(address);
    string tag = bit_tag.to_string();
    return tag.substr(0, tag_size);
}

void printState(int load_hits, int load_misses, int store_hits, int store_misses, int tot_cycles) {
    cout << "Total loads: " << load_hits + load_misses << endl;
    cout << "Total stores: " << store_hits + store_misses << endl;
    cout << "Load hits: " << load_hits << endl;
    cout << "Load misses: " << load_misses << endl;
    cout << "Store hits: " << store_hits << endl;
    cout << "Store misses: " << store_misses << endl;
    cout << "Total cycles: " << tot_cycles << endl;
}
