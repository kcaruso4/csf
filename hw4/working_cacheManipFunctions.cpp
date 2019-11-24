#include "cacheManipFunctions.h"

int performLoad(int& hits, int& misses, int& cycles, int evict, int num_blocks, int block_size, int num_sets, std::string index, std::string tag, Cache& cache, std::string& first_tag) {
    cSet* set_home = cache.findSet(index);
    cBlock* block;
    if (set_home->getNull()) {
        delete set_home;
        if (cache.getNumSets() == num_sets) {
            std::cerr << "Index is invalid" << std::endl;
            return -1;
        }
        misses++;
        set_home = cache.addSet(index);
        block = new cBlock(tag);
        set_home->addBlock(*block);
        first_tag = tag;
        cycles += 100 * (block_size / 4) + 1;
	    delete set_home;
	    delete block;
    }
    else {
        block = set_home->findBlock(tag);
        //checks if the block is in the set looking at
        //if not then a cache miss
        if (block->getNull()) {
            delete block;
            misses++;
            cycles += 100 * (block_size / 4) + 1;
            //check to see if is no more space in set
            //if no space evicts the block according to evict
            if (set_home->getNumBlocksStored() == num_blocks) {
                //get block that is least used or first added to set
	            block = set_home->findBlockAt(num_blocks - 1);

                //checks if the block is dirty
                //if dirty then need to write to memory
                if (block->getDirty()) {
                    cycles += 100 * (block_size / 4);
                    block->clearDirty();
                }

                set_home->incrementTimesAll();
                block->resetTime();
                block->updateTag(tag);
            }
            else {
                //increment time of all curent blocks
                set_home->incrementTimesAll();
                block = new cBlock(tag);
                set_home->addBlock(*block);
                delete block;
            }
        }
        else { //there is a block with the associated tag and cache hit
            hits++;
            cycles++;
            if (evict == 0) { //the cache is lru
                set_home->incrementTimesLru(block->getTime());
                block->resetTime();
            }
        }
    }
    set_home = NULL;
    block = NULL;
    return 0;
}

int storeWAWT(int& hits, int& misses, int& cycles, int evict, int num_blocks, int block_size, int num_sets, std::string index, std::string tag, Cache& cache, std::string& first_tag) {
    cSet* set_home = cache.findSet(index);
    cBlock* block;
    //check to see if the set is in the cache
    if (set_home->getNull()) {
        delete set_home;
        misses++;
        if (cache.getNumSets() == num_sets) {
            std::cerr << "Index is invalid " << std::endl;
            return -1;
        }
        //cylces for bringing block forward before perfroming store
        cycles += 100 * (block_size / 4);
        set_home = cache.addSet(index);
        block = new cBlock(tag);
        set_home->addBlock(*block);
        first_tag = tag;
        //cycles for storing to memory and storing to cache
        cycles += 101;
	    delete set_home;
	    delete block;
    }
    else { //set exists in cache
        block = set_home->findBlock(tag);

        //if the block is not in the set then miss
        if (block->getNull()) {
	        delete block;
	        misses++;
            //cycles for bringing block forward before performing store
            cycles += 100 * (block_size / 4);

            if (num_blocks == set_home->getNumBlocksStored()) { //max num of blocks in sets
	            block = set_home->findBlockAt(num_blocks - 1);
                set_home->incrementTimesAll();
                block->resetTime();
                block->updateTag(tag);

            }
            else {
                set_home->incrementTimesAll();
		        block = new cBlock(tag);
                set_home->addBlock(*block);
                delete block;
            }
            //cycles required to store to the cache and memory
            cycles += 101;
        }
        else { //block exists in set

            hits++;
            cycles += 101;
            if (evict == 0) { //cache is lru
                set_home->incrementTimesLru(block->getTime());
                block->resetTime();
            }
        }
    }
    set_home = NULL;
    block = NULL;
    return 0;
}

int storeWAWB(int& hits, int& misses, int& cycles, int evict, int num_blocks, int block_size, int num_sets, std::string& index, std::string tag, Cache& cache, std::string& first_tag, bool& dirty) {
    cSet* set_home = cache.findSet(index);
    cBlock* block;
    if (set_home->getNull()) {
        delete set_home;
        if (cache.getNumSets() == num_sets) {
            std::cerr << "Index is invalid " << std::endl;
            return -1;
        }
        misses++;
        //cylces for bringing block forward before perfroming store
        cycles += 100 * (block_size / 4);
        set_home = cache.addSet(index);
        block = new cBlock(tag);
        set_home->addBlock(*block);
        first_tag = tag;
        dirty = true;
        cycles ++;
	    delete set_home;
	    delete block;
    }
    else { //set exists in cache
        block = set_home->findBlock(tag);

        //if the block is not in the set then miss
        if (block->getNull()) {
	        delete block;
            misses++;
            //cycles for bringing block forward before performing store
            cycles += 100 * (block_size / 4);

            if (num_blocks == set_home->getNumBlocksStored()) { //max num of blocks in sets
	            block = set_home->findBlockAt(num_blocks - 1);
                //check if block is dirty
                if (block->getDirty()) {
                    //add cycles for updating memory
                    cycles += 100 * (block_size / 4);
                }
                set_home->incrementTimesAll();
                block->resetTime();
                block->updateTag(tag);
                block->setDirty();
            }
            else {
                set_home->incrementTimesAll();
		        block = new cBlock(tag);
                set_home->addBlock(*block);
                block->setDirty();
                delete block;
            }
            cycles ++;
        }
        else { //block exists in set
            hits++;
            cycles++;
            if (evict == 0) { //cache is lru
                set_home->incrementTimesLru(block->getTime());
                block->resetTime();
            }
        }
    }
    set_home = NULL;
    block = NULL;
    return 0;
}

int storeNWA(int& hits, int& misses, int& cycles, int evict, int num_sets, std::string index, std::string tag, Cache& cache) {
    cSet* set_home = cache.findSet(index);
    cBlock* block;
    //check to see if the set is in the cache
    if (set_home->getNull()) {
        delete set_home;
        misses++;
        if (cache.getNumSets() == num_sets) {
            std::cerr << "Index is invalid" << std::endl;
            return -1;
        }
        //only modify memory on miss
        cycles += 100;
    }
    else { //set exists in cache
        block = set_home->findBlock(tag);

        //if the block is not in the set then miss
        if (block->getNull()) {
	        delete block;
            misses++;
            cycles += 100;
        }
        else { //block exists in set
            hits++;
            cycles++;
            if (evict == 0) { //cache is lru
                set_home->incrementTimesLru(block->getTime());
                block->resetTime();
            }
        }
    }
    set_home = NULL;
    block = NULL;
    return 0;
}
