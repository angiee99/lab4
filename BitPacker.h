#pragma once

#include <fstream>
#include <vector>
#include "fileModule.h"

class BitPacker {
private: 
    uint8_t bitBuffer;
    uint8_t bitCount;
    std::ofstream outputFile;

    void resetBuffer();
    void writeByte(uint32_t byte);
public:
    BitPacker();
    ~BitPacker();

    void initWriter( const std::string& outputFName);

    void packBits(uint32_t bits, int lenght);
    
    void closeStream();
};