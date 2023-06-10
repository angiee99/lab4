#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>

#include "dictionary.h"
#include "fileModule.h"
#include "BitReader.h"

class Decoder {
private:
    Dictionary dictionary;
    BitReader reader;
    std::ofstream outputFile; 

public:
    void decode(const std::string& inputFilePath);

private:
    std::string entryFromCode(uint32_t code);

    void output(const std::string& entry);
};