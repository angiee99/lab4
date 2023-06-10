#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>

class Dictionary {
private:
    std::unordered_map<std::string, uint32_t> table;
    uint32_t maxEntries;
    uint32_t nextCodeInd;
    uint32_t currentLenght; 

public:
    Dictionary() ;

    // bool isLoaded() const 
    bool isFull() const ;

    bool includes(const std::string& key) const;

    uint32_t getCode(const std::string& key)const;

    void addCode(const std::string& key);

    uint32_t getCurrentSize();
    uint32_t getNextCode(); 

    std::string getString(uint32_t code) const;

    void clear();
private:
    void updateMaxEntries();
};