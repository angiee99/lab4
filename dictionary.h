#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>

class Dictionary {
private:
    std::unordered_map<std::string, uint32_t> table;
    uint32_t maxEntries;
    uint32_t nextCodeInd;
    int currentLenght; 

public:
    Dictionary() ;

    // bool isLoaded() const 
    bool isFull() const ;

    bool includes(const std::string& key) const;

    uint32_t getCode(const std::string& key)const;

    void addCode(const std::string& key);
    
    void clear();

    int getCurrentSize();

    std::string getString(uint32_t code) const;

private:
    void updateMaxEntries();
};