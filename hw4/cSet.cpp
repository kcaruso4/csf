#include <vector>
#include <iostream>
#include <string>
#include "cSet.h"

void cSet::addBlock(cBlock cb) {
    blocks.push_back(cb);
}

cBlock* cSet::findBlock(std::string tag) {
    int p_tag = stoi(tag, 0, 2);
    int b_tag;
    for (std::vector<cBlock>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
        b_tag = stoi(it->getTag(), 0, 2);
        if (b_tag == p_tag) {
            return &(*it);
        }
    }
    return new cBlock(0, true);
}

cBlock* cSet::getBlockEvict() {
    for (std::vector<cBlock>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
        if ((unsigned int) it->getTime() + 1 == blocks.size()) {
            return &(*it);
        }
    }
    return new cBlock(0, true);
}

void cSet::incrementTimesAll() {
    for (std::vector<cBlock>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
        it->incTime();
    }
}

void cSet::incrementTimesLru(int time) {
    for (std::vector<cBlock>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->getTime() < time) {
            it->incTime();
        }
        else if (it->getTime() == time){
            it->resetTime();
        }
    }
}

cBlock* cSet::findBlockAt(int time) {
    for (std::vector<cBlock>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->getTime() == time) {
            return &(*it);
        }
    }
    return new cBlock(0, true);
}

void cSet::setFirstBlock(std::string tag) {
    first_b_tag = tag;
}

void cSet::addFirstBlock() {
    cBlock* temp_b = new cBlock(first_b_tag);
    if (first_b_dirty) {
        temp_b->setDirty();
    }
    blocks.push_back(*temp_b);
    delete temp_b;
}

void cSet::setFirstDirty() {
    first_b_tag = true;
}
