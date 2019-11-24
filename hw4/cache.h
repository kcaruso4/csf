#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <string>
#include "cSet.h"

class Cache {
public:
    Cache(): num_sets_stored(0), num_sets(0), num_blocks(0),block_size(0), cache_store(0), mem_write(0), evict(0), load_hits(0), load_misses(0), store_hits(0), store_misses(0), num_cycles(0) {};

    Cache(int sn, int bn, int bs, int cs, int mw, int e) {
        num_sets_stored = 0;
        num_sets = sn;
        num_blocks = bn;
        block_size = bs;
        cache_store = cs;
        mem_write = mw;
        evict = e;
        load_hits = 0;
        load_misses = 0;
        store_hits = 0;
        store_misses = 0;
        num_cycles = 0;
    }

    //adds a new set to the vector and retuns the set it just added
    cSet* addSet(std::string index);

    //write function that checks to see if a block is in the cache_store
    //returns the block if found, else null
    cSet* findSet(std::string index);

    //This funciton returns the number of sets stored in the cache
    int getNumSets() { return num_sets_stored; }

    //This function preforms a load trace on the cache
    //If the load was successful return 0, else -1
    int performLoad(std::string index, std::string tag, std::string& first_tag);

    //This function performs a store trace on the cache
    //If the store was successful return 0 else -1
    int performStore(std::string index, std::string tag, std::string& first_tag, bool& dirty);

    //This function prints the final statistics about the cache performance
    void printState();

private:
    std::unordered_map<std::string, cSet>sets; //contains the sets in the cache
    int num_sets_stored;    //counts the number of sets stored
    int num_sets;
    int num_blocks;
    int block_size;
    int cache_store;
    int mem_write;
    int evict;
    int load_hits;
    int load_misses;
    int store_hits;
    int store_misses;
    int num_cycles;
} ;

#endif
