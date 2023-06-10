#pragma once

#include <fstream>
#include <vector>
#include <array>

class BitReader {
private:
    std::ifstream inputFile;
    uint8_t bitBuffer;
    uint8_t bitCount;
    unsigned char readChar; 
    int bitMasks[9];

public:
    BitReader();

    std::string setStream(std::string inputFileName);

    bool hasData() ;
    
    uint32_t readCode(int lenght);

    void closeStream();

};