#include "dictionary.h"
#include <iostream>
//          - initially 9 bits
//         - at 512 entries 10 bits
//         - at 1025 entries at 11 bits
//         - at 2048 entries 12 bits
Dictionary:: Dictionary() {
    maxEntries = 512;
    nextCodeInd = 0;
    currentLenght = 9; 
    // starter single-character codes
    for (uint32_t i = 0; i < 256; ++i) {
        table[std::string(1, static_cast<char>(i))] = nextCodeInd++;
        // table[std::string(1, i)] = nextCodeInd++;
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
int Dictionary::getCurrentSize(){
    return currentLenght; 
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
        currentLenght = 12;
        maxEntries = 4096;
    } else if (nextCodeInd >= 1025) {
        currentLenght = 11;
        maxEntries = 2048;
    } else if (nextCodeInd >= 512) {
        currentLenght = 10;
        maxEntries = 1025;
    }
}

std::string Dictionary::getString(uint32_t code) const {
    for (std::unordered_map<std::string, uint32_t>::const_iterator 
            it = table.begin(); it != table.end(); ++it) {
        if (it->second == code) { // If a match is found, it returns the string associated with that code
            return it->first;
        }
    }
    return ""; // Return empty string if code not found in the dictionary
}
