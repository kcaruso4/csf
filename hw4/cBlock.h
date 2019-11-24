#ifndef CBLOCK_H
#define CBLOCK_H

#include <string>

class cBlock {
public:
    cBlock(): dirty(false), time(0), tag(""), null_val(false) {}
    cBlock(std::string id) {
        dirty = false;
        time = 0;
        tag = id;
        null_val = false;
    }
    cBlock(std::string id, bool dirt) {
        dirty = dirt;
        time = 0;
        tag = id;
        null_val = false;
    }
    cBlock(int i, bool nul) {
        dirty = false;
        time = 0;
        tag = "";
        null_val = nul;
        place_holder = i;
    }

    //marks the block as dirty
    void setDirty();

    //resets the dirty value
    void clearDirty();

    //increment time
    void incTime();

    //reset the time field
    void resetTime();

    //update the tag
    void updateTag(std::string newt);

    //get the time
    int getTime() { return time; }

    //get the tag
    std::string getTag() { return tag; }

    //get the dirty state
    bool getDirty() { return dirty; }

    //This function returns whether or not a block is null
    //Used for checking if a block is in a set
    bool getNull() { return null_val; }

    //This function sets the null field of a block to true;
    void setNull();

private:
    bool dirty; // checks if block is dirty
    int time;   //number of time spent in ccache
    std::string tag;   //tags that identifies the blocks
    bool null_val;  //used to create a 'null' block
    int place_holder;
} ;

#endif
