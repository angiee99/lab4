#include "BitReader.h"

BitReader::BitReader() {
    bitBuffer = 0; 
    bitCount = 0; 
    readChar = 0; 
    for(int i = 0; i< 9; i++){
        bitMasks[i] = pow(2, i) - 1;
    }
    // 0x00 0x01 0x03 0x07 0x0F 0x1F 0x3F 0x7F 0xFF
} 

BitReader::~BitReader(){
    if (inputFile.is_open())
        inputFile.close(); 
}

std::string  BitReader::setStream(std::string inputFileName) {
    inputFile.open(inputFileName, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Failed to open input file: " + inputFileName);
    }

    std::string str;
    char c;
    // read characters until the separator
    while (inputFile.read(&c, sizeof(char)) && c != 'N') {
        str += c;
    }
    return str;
}

bool BitReader::hasData() {
    return !inputFile.eof();
}


uint16_t BitReader::readCode(int bitsToRead) {
        // take what is left in buffr
    uint16_t code = bitBuffer;    // code - result of the readCode
    std::size_t addedBitsCount = bitCount;  // bits already added to code
    bitsToRead -= bitCount; // bits left to read 
   
    //reset buffer
    bitCount = 0;       
    bitBuffer = 0;

    // read char from file 
    while (bitsToRead != 0 && inputFile.get((char&)(readChar))) {
        // 8+ bits to read
        if (bitsToRead >= 8) {
            // add the readChar to the code, potentially with remaining bits from the buffer
                // code = 101
                // readChar = 11001100
                // 11001100 << 3 = 11001100000 = 01100000
                // code = 11001100000 | 101 =    01100101
            code |= static_cast<uint16_t>(readChar) << addedBitsCount;
            addedBitsCount += 8; 
            bitsToRead -= 8;
        } else {
            // less than 8 bits -> using mask add to code what can add, the rest store in buffer
                // readChar = 11001100 
                // bitsToRead = 6 
                // 11001100 & 0x3F = 00001100 
                // 00001100 << 9 = 00001100000000000
            code |= static_cast<uint16_t>(readChar & bitMasks[bitsToRead]) << addedBitsCount;
            bitCount = 8 - bitsToRead; // update the bitCount for the remaining buffer size
            bitBuffer = readChar >> bitsToRead; // add what is left to the buffer
            //bitBuffer = 11001100 >> 6 = 00000011
            break;
        }
    }
    return code;
}

void BitReader::closeStream(){
    inputFile.close();
}
