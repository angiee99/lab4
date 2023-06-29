#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "dictionary.h"
#include "fileModule.h"
#include "BitPacker.h"

class Encoder {
private:
    Dictionary dictionary;
    BitPacker writer; 
    std::ifstream inputFile; 

public:
    ~Encoder();
    void encode(const std::string& inputFilePath, const std::string& outputFilePath);
    void packCode(uint16_t code);
};