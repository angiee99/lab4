#include "BitReader.h"

BitReader::BitReader() {
    bitBuffer = 0; 
    bitCount = 0; 
    readChar = 0; 
    // for(int i = 0; i< 9; i++){
    //     bitMasks[i] = pow(2, i) - 1;
    // }
    // 0x00 0x01 0x03 0x07 0x0F 0x1F 0x3F 0x7F 0xFF
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
        // return 
    }
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
    //length початково дорівнює розміру поточного макс коду в таблиці (9 - 12),  скількі бітів лишилось зчитати 
    
    std::size_t addedBitsCount = 0; // скільки з минулого читання лишилось 

    // усе що лишалось в буфері записуємо у поточний код поки
    if(bitCount > 0){
        
        code = bitBuffer;   //101		// заповнили код кешем 
        lenght -= bitCount; // length = 9-3 = 6   // лишилось наш код заповнити вже на меншу кількість бітів
        addedBitsCount = bitCount; 
        bitCount = 0;       // ресет буфер
        bitBuffer = 0;
    }
   
    // нове читання з файлу
    while (lenght != 0 && inputFile.get(reinterpret_cast<char &>(readChar)))
    {
        // треба ще записати 8+ бітів
        if (lenght >= 8)
        {
            // додати до коду, де потенційно є залишок з буферу 
            // зчитаний символ, в результаті отримати байт у коді
                // readChar = 11001100
                // 11001100 << 3 = 11001100000 = 01100000
                // code = 11001100000 | 101 =    01100101 
            code |= static_cast<uint32_t>(readChar) << addedBitsCount;
            addedBitsCount += 8; 
            lenght -= 8;
        }
        else
        {
            // менше ніж 8 бітів -> за доп маски комбінуємо потрібни 8 у код
                // readChar = 11001100 
                // lenght = 6 
                // 11001100 & 0x3F = 00001100 
                // 00001100 << 9 = 00001100000000000
            code |= static_cast<uint32_t>(readChar & bitMasks[lenght]) << addedBitsCount;
            bitCount = 8 - lenght; //записати розмір буферу, який зараз оновиться
            bitBuffer = readChar >> lenght; // записати у буфер те, що не увійшло в код
                //bitBuffer = 11001100 >> 6 = 00000011
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