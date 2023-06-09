#include "dictionary.h"
#include <iostream>
//              < 256   8 bits
//          256 - 512   9 bits
//          512 - 1025  10 bits
//         1025 - 2048  11 bits
//              > 2048  12 bits 

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
// returns the code value that represents the string
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
// returns the string that corresponds to the given code
std::string Dictionary::getString(uint32_t code) const {
    for (std::unordered_map<std::string, uint32_t>::const_iterator 
            it = table.begin(); it != table.end(); ++it) {
        if (it->second == code) { // If a match is found, it returns the string associated with that code
            return it->first;
        }
    }
    return ""; // Return empty string if code not found in the dictionary
}
