#pragma once

#include <fstream>

class BitReader {

    std::ifstream inputFile;
    uint8_t bitBuffer;
    uint8_t bitCount;
    unsigned char readChar; 
    int bitMasks[9];

public:
    BitReader();
    ~BitReader();

    std::string setStream(std::string inputFileName);

    bool hasData() ;
    
    uint16_t readCode(int lenght);

    void closeStream();

};