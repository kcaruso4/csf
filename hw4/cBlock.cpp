#include "cBlock.h"

//marks the block as dirty
void cBlock::setDirty() {
    dirty = true;
}

//resets the dirty value
void cBlock::clearDirty() {
    dirty = false;
}

//increment time
void cBlock::incTime() {
    time++;
}

//reset the time field
void cBlock::resetTime() {
    time = 0;
}

//update the tag
void cBlock::updateTag(std::string newt) {
    tag = newt;
}

void cBlock::setNull() {
    null_val = true;
}
