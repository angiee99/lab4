#include "dictionary.h"

Dictionary:: Dictionary() {
    maxEntries = 512;
    nextCodeInd = 0;
    currentLenght = 9; 
    // starter single-character codes
    for (uint16_t i = 0; i < 256; ++i) {
        table[std::string(1, static_cast<char>(i))] = nextCodeInd++;
    }
}
bool Dictionary::isFull()  {
    return nextCodeInd >= maxEntries;
}

bool Dictionary::includes(const std::string& key) {
    return table.count(key)> 0;
    
}
// returns the code value that represents the string
uint16_t Dictionary::getCode(const std::string& key){
    return table.at(key); 
}
uint16_t Dictionary::getCurrentSize(){
    return currentLenght; 
}
uint16_t Dictionary::getNextCode(){
    return nextCodeInd+1; 
}
void Dictionary::addCode(const std::string& key) {
    if (!isFull() && !includes(key)) {
        table[key] = nextCodeInd++;
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
std::string Dictionary::getString(uint16_t code) {
    for (std::unordered_map<std::string, uint16_t>::const_iterator 
            it = table.begin(); it != table.end(); ++it) {
        if (it->second == code) { // if a match is found, it returns the string associated with that code
            return it->first;
        }
    }
    return ""; // Return empty string if code not found in the dictionary
}
