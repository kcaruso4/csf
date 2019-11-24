#include <iostream>
#include <unordered_map>
#include <string>
#include <bitset>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "argsHandlingFunctions.h"
#include "cSet.h"
#include "cBlock.h"
#include "cache.h"

#define ADD_LENGTH 32

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::unordered_map;
using std::bitset;
using std::string;
using std::fstream;
using std::invalid_argument;
using std::out_of_range;
using std::stoi;
using std::log;
using std::pow;
using std::vector;
using std::hex;

int main(int argc, char *argv[]) {

    //check to see if enough arguments are provided in the command line
    if (argc < 7) {
        cerr << "Not enough arguments provided" << endl;
        return 1;
    }
    else if (argc > 7) {
        cerr << "Too many arguments provided" << endl;
        return 1;
    }

    int set_num = 0;
    int block_num = 0;
    int block_size = 0;
    int cache_store = 0;
    int mem_write = 0;
    int evict = 0;

    //check validity of the arguments
    int check = makeInt(argv[1]);
    if (check == -1) {
        return 1;
    }
    set_num = stoi(argv[1]);

    check = makeInt(argv[2]);
    if (check == -1) {
        return 1;
    }
    block_num = stoi(argv[2]);
    check = makeInt(argv[3]);
    if (check == -1) {
        return 1;
    }

    block_size = stoi(argv[3]);
    if (block_size < 4) {
        cerr << "Number of bytes in blocks must be at least 4" << endl;
        return 1;
    }

    cache_store = checkStoreMiss(argv[4]);
    if (cache_store == -1) {
        return 1;
    }

    mem_write = checkStoreWrite(argv[5]);
    if (mem_write == -1) {
        return 1;
    }
    if (cache_store == 1 && mem_write == 1) {
        cerr << "Cannot designate no-write-allocate and write-back together" << endl;
        return 1;
    }

    evict = checkEvict(argv[6]);
    if (evict == -1) {
        return 1;
    }

    //determines which bits of the address will identify which piece in the cache
    int num_bit_index = getPowerTwo(set_num);
    int num_bit_offset = getPowerTwo(block_size);
    if (num_bit_index == -1 || num_bit_offset == -1) {
        return 1;
    }
    int num_bit_tag = ADD_LENGTH - num_bit_offset - num_bit_index;

    //create cache
    Cache cache = Cache(set_num, block_num, block_size, cache_store, mem_write, evict);

    //create trace command variables
    char operation;
    unsigned int address;
    int forget;
    string first_tag = "";
    bool dirty = false;
    bool trace_succes = false;;
    while (cin >> operation >> hex >> address >> forget) {
        string index = getTraceIndex(num_bit_index, num_bit_tag, address);
        string tag = getTraceTag(num_bit_tag, address);
        if (operation == 'l') {
            check = cache.performLoad(index, tag, first_tag);
            if (check != 0) {
                cerr << "Failure in performing load." << endl;
                return 1;
            }
        }
        else if (operation == 's') {
            check = cache.performStore(index, tag, first_tag, dirty);
            if (check == -1) {
                cerr << "Failure in performing store." << endl;
                return 1;
            }
        }
        else {
            cerr << "Invalid operation" << endl;
            return 1;
        }
        if (cache.findSet(index)->getNumBlocksStored() == 0) {
            cBlock* b = new cBlock(tag);
            if (dirty) {
                b->setDirty();
                dirty = false;
            }
            cache.findSet(index)->addBlock(*b);
            delete b;
        }
        trace_succes = true;
    }
    if (!trace_succes && first_tag.compare("") != 0) {
        cerr << "Failed trace" << endl;
        return 1;
    }
    cache.printState();
    return 0;

}
