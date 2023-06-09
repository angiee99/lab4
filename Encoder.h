#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "dictionary.h"
#include "fileModule.h"
#include "BitWriter.h"

class Encoder {
private:
    Dictionary dictionary;
    std::vector<uint32_t> encodedData; //mb dont need
    BitWriter writer; 

public:
    void  encode(const std::string& inputFilePath, const std::string& outputFilePath);
    void  packCode(uint32_t code);
    
};