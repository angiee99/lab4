#pragma once

#include <fstream>
#include <vector>
#include <array>

class BitReader {
private:
    std::ifstream inputFile;
    unsigned char readChar; 
    uint8_t bitBuffer;
    uint8_t bitCount;

    int bitMasks[9];

public:
    BitReader();

    void setStream(std::string inputFileName);

    bool hasData() ;
    
    uint32_t _readCode();

    uint32_t readCode(int lenght);

    void closeStream();

private:
    uint8_t readBit();

    void readByte();
};