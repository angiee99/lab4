#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "dictionary.h"
#include "BitReader.h"

class Decoder {
    Dictionary dictionary;
    BitReader reader;
    std::ofstream outputFile; 
    void output(const std::string& entry);

public:
    void decode(const std::string& inputFilePath);
    std::string entryFromCode(uint16_t code);
    
};