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
    // mb std::ifstream inputFile; 

public:
    void encode(const std::string& inputFilePath, const std::string& outputFilePath);
    void packCode(uint32_t code);
};