#pragma once

#include <vector>
class BitWriter {
private: 
    std::vector<uint8_t>  packedData;
    uint8_t bitBuffer;
    uint8_t bitCount;
public:
    BitWriter(){
        bitBuffer = 0;
        bitCount = 0;
    }
    void flushBuffer() {
        if (bitCount > 0) {
            packedData.push_back(bitBuffer);
        }
        bitBuffer = 0;
        bitCount = 0;
    }

    void writeBit(bool bit) {
        bitBuffer |= (bit << (7 - bitCount));
        bitCount++;
        if (bitCount == 8) {
            packedData.push_back(bitBuffer);
            bitBuffer = 0;
            bitCount = 0;
        }
    }

    uint8_t writeBits(uint32_t bits, uint8_t bitLength) {
        for (int8_t i = bitLength - 1; i >= 0; --i) {
            bool bit = (bits >> i) & 1;
            writeBit(bit);
        }
        return bitBuffer; 
    }

};