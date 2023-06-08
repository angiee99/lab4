#include "dictionary.h"
#include <iostream>

Dictionary:: Dictionary() {
    maxEntries = 512;
    nextCodeInd = 0;

    // starter single-character codes
    for (uint32_t i = 0; i < 256; ++i) {
        table[std::string(1, static_cast<char>(i))] = nextCodeInd++;
    }
}
bool Dictionary::isFull() const {
    return nextCodeInd >= maxEntries;
}

bool Dictionary::includes(const std::string& key) const {
    return table.count(key)> 0; //
    
}

uint32_t Dictionary::getCode(const std::string& key)const{
    return table.at(key);
}

void Dictionary::addCode(const std::string& key) {
    if (!isFull() && !includes(key)) {
        table[key] = nextCodeInd++;
        std::cout << key << ", " << table[key]<< std::endl;
        updateMaxEntries();
    }
}
void Dictionary::clear(){
    table.clear();
    nextCodeInd = 0;
    updateMaxEntries();
}

void Dictionary::updateMaxEntries() {
    if (nextCodeInd >= 2048) {
        maxEntries = 4096;
    } else if (nextCodeInd >= 1025) {
        maxEntries = 2048;
    } else if (nextCodeInd >= 512) {
        maxEntries = 1025;
    }
}