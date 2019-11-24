#ifndef CSET_H
#define CSET_H

#include <vector>
#include <iostream>
#include "cBlock.h"

class cSet {
public:
    //cSet(): index(""), null(false), place_holder(0), first_b_tag(""), first_b_dirty(false) {};
    cSet(): null(false), first_b_tag(""), first_b_dirty(false) {};
    /*cSet(std::string s) {
        index = s;
        null = false;
        place_holder =0 ;
        first_b_tag = "";
        first_b_dirty = false;
    }*/
    /*cSet(int i ,bool nul) {
        //index = "";
        null = nul;
        //place_holder = i;
        first_b_tag = "";
        first_b_dirty = false;
    }*/
    cSet(bool nul) {
        null = nul;
        first_b_tag = "";
        first_b_dirty = false;
    }

    //adds a block to the a new list
    void addBlock(cBlock cb);

    //finds the index of a block, returns -1 if not found
    cBlock* findBlock(std::string tag);

    //find block to evict for lru
    cBlock* getBlockEvict();

    //void get index
    //std::string getIndex() { return index; }

    //returns the number of blocks stored
    int getNumBlocksStored() { return blocks.size(); }

    //This function increments the times of all the block
    //This function is used for when a block is evicted and another is
    //added in it's place so all the others must be incremented
    void incrementTimesAll();

    //This function increases the times of blocks that are less than the given
    //time from the block currently being used. This function is used to
    //implement lru eviction
    void incrementTimesLru(int time);

    //This fucntion returns the cBlock with the given time field.
    //If a block with that time field cannot be found will return null.
    cBlock* findBlockAt(int time);

    //This function returns null if initalized as so. Use this function
    //during error checking for when the set is not in the cache
    bool getNull() { return null; }

    //This function sets the sets the first block
    void setFirstBlock(std::string tag);

    //This function reads the first block
    void addFirstBlock();

    //This function sets the dirty value true if the first block
    //to be added is dirty
    void setFirstDirty();


private:
    //std::string index; //index of the set
    std::vector<cBlock> blocks;
    bool null; //used to condition check
    //int place_holder; //holds place
    std::string first_b_tag;
    bool first_b_dirty;
} ;

#endif
