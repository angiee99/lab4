#pragma once

#include <fstream>

class BitPacker {
    uint8_t bitBuffer;
    uint8_t bitCount;
    std::ofstream outputFile;

    void resetBuffer();
    void writeByte(uint16_t byte);
public:
    BitPacker();
    ~BitPacker();

    void initWriter( const std::string& outputFName, const std::string& inputFName);

    void packBits(uint16_t bits, int lenght);
    
    void writeLast();
    void closeStream();
};