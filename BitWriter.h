#pragma once

#include <fstream>
#include <vector>
#include "fileModule.h"

class BitWriter {
private: 
    std::vector<uint8_t>  packedData;
    uint8_t bitBuffer;
    uint8_t bitCount;
    std::ofstream outputFile;
    
public:
    BitWriter(){
        bitBuffer = 0;
        bitCount = 0;
        outputFile.open("output2.bmp", std::ios::binary);
    }

    void flushBuffer() {
        if (bitCount > 0) {
            packedData.push_back(bitBuffer);
        }
        bitBuffer = 0;
        bitCount = 0;
    }

    void writeBit(int8_t bit) {
        bitBuffer |= (bit << (7 - bitCount));
        bitCount++;
        if (bitCount == 8) {
            packedData.push_back(bitBuffer);
            bitBuffer = 0;
            bitCount = 0;
        }
    }

    void writeBits(uint32_t bits, uint8_t bitLength, int bit_lenght) {
            // How many bits to write
        std::size_t leftBits = bit_lenght;

        // Handle bits left from the previous writing
        if (bitCount != 0)
        {
            // Adding as many bits as possible to the remaining byte
            bitBuffer |= bits << bitCount;

            // Writing a complete byte to the file
            outputFile.put(static_cast<char>(bitBuffer));

            // Removing bits that were already written
            bits >>= 8 -bitCount;

            // Decreasing the number of the remaining bits
            leftBits -= 8 - bitCount;

            // Reseting a buffer
            bitCount = 0;
            bitBuffer = 0;
        }

        // Write rest of the bits
        while (leftBits != 0)
        {
            // More than a whole byte left
            if (leftBits >= 8)
            {
            outputFile.put(static_cast<char>(bits));
            bits >>= 8;
            leftBits -= 8;
            }
            else // Cache left bits
            {
            bitCount = leftBits;
            bitBuffer = bits;
            break;
            }
        }

    }
    
    void closeStream(){
        outputFile.close();
    }
    void _writeBits(uint32_t bits, uint8_t bitLength, int lenght) {
        // for (int8_t i = bitLength - 1; i >= 0; --i) {
        //     int8_t bit = (bits >> i) & 1;
        //     writeBit(bit);
        // }
        if( bitCount > 0){
            bitBuffer |= bits << bitCount; 
            packedData.push_back(bitBuffer); //
            outputFile.put(static_cast<char>(bitBuffer));  // file.put(static_cast<char> (bitBuffer) )
            bits >>= 8  - bitCount; // shifting for 'clearing' bits that were written
            lenght -= 8 - bitCount;

            bitBuffer = 0;
            bitCount = 0;
        }
        while(lenght > 0){
            if(lenght >=8){ //?? 
                packedData.push_back(static_cast<uint8_t>(bits)); // file.put(static_cast<char> (bitBuffer) )
                outputFile.put(static_cast<char>(bits));
                bits >>= 8;
                lenght -= 8; 
            }
            else{ //add whats left to buffer
                bitCount = lenght; 
                bitBuffer = bits;
                break;
            }
        }
    
    }
    
    std::vector<uint8_t> getPackedData(){
        return packedData; 
    }

    void writeBytes(const std::vector<uint8_t>& bytes) {
        outputFile.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    }

};