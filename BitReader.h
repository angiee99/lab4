#pragma once

#include <fstream>
#include <vector>

class BitReader {
private:
    std::ifstream inputFile;
    unsigned char readChar; 
    uint8_t bitBuffer;
    uint8_t bitCount;

public:
    BitReader() : bitBuffer(0), bitCount(0), readChar(0) {}

    void setStream(std::string inputFileName) {
        inputFile.open(inputFileName, std::ios::binary);
        if (!inputFile) {
            throw std::runtime_error("Failed to open input file: " + inputFileName);
        }
        // inputFile = std::move(*stream);
        inputFile.seekg(0, std::ios::end);
        uint64_t fileSize = inputFile.tellg();
        inputFile.seekg(0, std::ios::beg);
        readByte(); // Read the first byte into the bit buffer
    }

    bool hasData() {
        return !inputFile.eof();
    }

    uint32_t readCode() {
        uint32_t code = 0;

        for (int8_t i = 0; i < 32; ++i) {
            uint8_t bit = readBit();
            code |= (bit << i);
        }

        return code;
    }
    void closeStream(){
        inputFile.close();
    }

private:
    bool readBit() {
        if (bitCount == 0) {
            readByte();
        }

        uint8_t bit = (bitBuffer >> 7) & 1;
        bitBuffer <<= 1;
        --bitCount;

        return bit;
    }

    void readByte() {
        inputFile.get(reinterpret_cast<char&>(readChar));
        bitCount = 8;
    }
};