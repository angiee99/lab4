#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Encoder.h"
#include "Decoder.h"

class Archiver {
private:
    Encoder encoder; 
    Decoder decoder; 
public:
    void compress(const std::string& inputFile, const std::string& outputFile);

    void decompress(const std::string& inputFile);
};