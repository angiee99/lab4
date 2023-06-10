#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Encoder.h"
#include "Decoder.h"

class Archiver {
    Encoder encoder; 
    Decoder decoder; 
    CompressedFileValidator validator;
public:

    void compress(const std::string& inputFile, const std::string& outputFile);

    void decompress(const std::string& inputFile);
};