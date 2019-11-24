#include <unordered_map>
#include <map>
#include <string>
#include "cache.h"

cSet* Cache::addSet(std::string index) {
    cSet* temp_s = new cSet();
    sets[index] = *temp_s;
    num_sets_stored++;
    return temp_s;
}

cSet* Cache::findSet(std::string index) {
    std::unordered_map<std::string, cSet>::iterator it = sets.find(index);
    cSet temps;
    if (it != sets.end()) {
        return &sets[index];
    }
    return new cSet(true);
}

int Cache::performLoad(std::string index, std::string tag, std::string& first_tag) {
    cSet* set_home = findSet(index);
    cBlock* block;
    if (set_home->getNull()) {
        //if the set is not in the cache
        delete set_home;  //free memory
        if (getNumSets() == num_sets) {
            //checks to make sure index is valid
            std::cerr << "Index is invalid" << std::endl;
            return -1;
        }
        load_misses++;
        //add set and add block
        set_home = addSet(index);
        block = new cBlock(tag);
        set_home->addBlock(*block);
        first_tag = tag;
        num_cycles += 100 * block_size / 4 + 1;
        delete set_home;
        delete block;
    }
    else {
        block = set_home->findBlock(tag);
        if (block->getNull()) {
            delete block;
            load_misses++;
            num_cycles += 100 * block_size / 4 + 1;
            if (set_home->getNumBlocksStored() == num_blocks) {
                //no more room to add blocks in set
                //must evict

                //finds oldest block according to eviction order
                block = set_home->findBlockAt(num_blocks - 1);

                //checks if block is dirty
                if (mem_write == 1 && block->getDirty()) {
                    num_cycles += 100 * block_size / 4;
                    block->clearDirty();
                }

                set_home->incrementTimesAll();
                block->resetTime();
                block->updateTag(tag);
            }
            else {
                //is space to add block to set
                set_home->incrementTimesAll();
                block = new cBlock(tag);
                set_home->addBlock(* block);
                delete block;
            }
        }
        else {
            //block is found
            load_hits++;
            num_cycles++;
            if (evict == 0) { // cache is lru
                set_home->incrementTimesLru(block->getTime());
            }
        }
    }
    set_home = NULL;
    block = NULL;
    return 0;
}

int Cache::performStore(std::string index, std::string tag, std::string& first_tag, bool& first_dirty) {
    cSet* set_home = findSet(index);
    cBlock* block;
    if (set_home->getNull()) {
        //set is not in the cache
        delete set_home;
        store_misses++;
        if (getNumSets() == num_sets) {
            //index is invalid
            std::cerr << "Index is invalid" << std::endl;
            return -1;
        }
        if (cache_store == 0) { //cache is write-allcoate
            set_home = addSet(index);
            block = new cBlock(tag);
            set_home->addBlock(*block);
            first_tag = tag;
            first_dirty = true;
            delete set_home;
            delete block;
            num_cycles += 100 * block_size / 4;
            if (mem_write == 0) {
                num_cycles += 101;
            }
            else {
                num_cycles++;
            }
        }
        else {
            num_cycles += 100;
        }
    }
    else {
        //set is found
        block = set_home->findBlock(tag);
        if (block->getNull()) {
            //block does not exist in set
            delete block;
            store_misses++;
            if (cache_store == 0) {
                //write allocate
                if (num_blocks == set_home->getNumBlocksStored()) {
                    //no more room in set
                    block = set_home->findBlockAt(num_blocks - 1);
                    //if write-back, checks block to see if it's dirty
                    if (mem_write == 1 && block->getDirty()) {
                        num_cycles += 100 * block_size / 4;
                    }
                    set_home->incrementTimesAll();
                    block->resetTime();
                    block->updateTag(tag);
                }
                else {
                    //there is room in the set to add block
                    set_home->incrementTimesAll();
                    block = new cBlock(tag);
                    set_home->addBlock(*block);
                    if (mem_write == 1) {
                        block->setDirty();
                    }
                    delete block;
                }
                if (cache_store == 0) { // write-allocate
                    num_cycles += 100 * block_size / 4;
                    if (mem_write == 0) { //writhe through
                        num_cycles += 101;
                    }
                    else {
                        num_cycles++;
                    }
                }
            }
            else {
                num_cycles += 100;
            }
        }
        else {
            //block is found
            store_hits++;
            if (mem_write == 1) {
                block->setDirty();
            }
            if (cache_store == 1) { //no write allocate
                num_cycles += 100;
            }
            else if (mem_write == 0) { //write allocate and write through
                num_cycles += 101;
            }
            else {
                num_cycles++;
            }
            if (evict == 0) {
                set_home->incrementTimesLru(block->getTime());
            }
        }
    }
    set_home = NULL;
    block = NULL;
    return 0;
}

void Cache::printState() {
    std::cout << "Total loads: " << load_hits + load_misses << std::endl;
    std::cout << "Total stores: " << store_hits + store_misses << std::endl;
    std::cout << "Load hits: " << load_hits << std::endl;
    std::cout << "Load misses: " << load_misses << std::endl;
    std::cout << "Store hits: " << store_hits << std::endl;
    std::cout << "Store misses: " << store_misses << std::endl;
    std::cout << "Total cycles: " << num_cycles << std::endl;
}
