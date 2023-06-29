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
    std::ofstream outputFile; //make sure that fstream is closed (read more IDisposable interface and pattern)
    void output(const std::string& entry);

public:
    ~Decoder(); 
    void decode(const std::string& inputFilePath);
    std::string entryFromCode(uint16_t code);
    
};