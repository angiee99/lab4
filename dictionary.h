#pragma once

#include <unordered_map>
#include <string>

class Dictionary {

    std::unordered_map<std::string, uint16_t> table;
    uint16_t maxEntries;
    uint16_t nextCodeInd;
    uint16_t currentLenght; 

    void updateMaxEntries();
public:
    Dictionary();

    bool isFull();

    bool includes(const std::string& key);

    uint16_t getCode(const std::string& key);

    void addCode(const std::string& key);

    uint16_t getCurrentSize();
    uint16_t getNextCode(); 

    std::string getString(uint16_t code) ;

    void clear();

};