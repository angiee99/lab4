#include "BitReader.h"
   
BitReader::BitReader() {
    bitBuffer = 0; 
    bitCount = 0; 
    readChar = 0; 
    bitMasks[0] = 0x00;
    bitMasks[1] = 0x01;
    bitMasks[2] = 0x03;
    bitMasks[3] = 0x07;
    bitMasks[4] = 0x0F;
    bitMasks[5] = 0x1F;
    bitMasks[6] = 0x3F;
    bitMasks[7] = 0x7F;
    bitMasks[8] = 0xFF;
} 

    void BitReader::setStream(std::string inputFileName) {
        inputFile.open(inputFileName, std::ios::binary);
        if (!inputFile) {
            throw std::runtime_error("Failed to open input file: " + inputFileName);
        }
        // inputFile = std::move(*stream);
        // inputFile.seekg(0, std::ios::end);
        // uint64_t fileSize = inputFile.tellg();
        // inputFile.seekg(0, std::ios::beg);
        // readByte(); // Read the first byte into the bit buffer
    }

    bool BitReader::hasData() {
        return !inputFile.eof();
    }
    
    uint32_t BitReader::_readCode() {
        uint32_t code = 0;

        for (int8_t i = 0; i < 32; ++i) {
            uint8_t bit = readBit();
            code |= (bit << i);
        }

        return code;
    }

    uint32_t BitReader::readCode(int lenght) {
        uint32_t code; // сюди зчитуємо 
        std::size_t leftBits = lenght ;  // скількі бітів лишилось зчитати 
                         //початково дорівнює розміру поточного макс коду в таблиці (9 - 12)
        
        std::size_t offset = bitCount; // скільки з минулого читання лишилось 

        unsigned char charRead; 

        // Write out leftovers from the buffer
        code = bitBuffer;   		// заповнив код кешем 
        leftBits -= bitCount;       // лишилось наш код заповнити вже на меншу кількість бітів
        bitCount = 0;               // почистив кеш 
        bitBuffer = 0;

        // Reading what's left to read
        while (leftBits != 0 && inputFile.get(reinterpret_cast<char &>(charRead)))
        {
            // More than a byte left
            if (leftBits >= 8)
            {
                // Add a new byte to our code, taking into account bits
                // that were already added
                code |= static_cast<uint32_t>(charRead) << offset;
                offset += 8;
                leftBits -= 8;
            }
            else
            {
                // Using a bit mask to add only bits that's left and no more
                code |= static_cast<uint32_t>(charRead & bitMasks[leftBits]) << offset;
                bitCount = 8 - leftBits;
                bitBuffer = charRead >> leftBits;
                break;
            }
        }

        return code;

}

    void BitReader::closeStream(){
        inputFile.close();
    }


    uint8_t BitReader::readBit() {
        if (bitCount == 0) {
            readByte();
        }

        uint8_t bit = (bitBuffer >> 7) & 1;
        bitBuffer <<= 1;
        --bitCount;

        return bit;
    }

    void BitReader::readByte() {
        inputFile.get(reinterpret_cast<char&>(readChar));
        bitCount = 8;
    }