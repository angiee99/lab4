#include "BitPacker.h" 
BitPacker::BitPacker(){
    bitBuffer = 0;
    bitCount = 0;
}
BitPacker::~BitPacker(){
    if (outputFile.is_open())
        outputFile.close();
}
// ~ if outputFile -> close it

void BitPacker::initWriter( const std::string& outputFName){
    outputFile.open(outputFName, std::ios::binary);
    if (!outputFile)
        throw std::runtime_error("Failed to open output file"); //mb return

}

void BitPacker::resetBuffer() {

    bitBuffer = 0;
    bitCount = 0;
}

void BitPacker::packBits(uint32_t bits, int lenght) {
    if( bitCount > 0){ // if there are bits in buffer left from last time 
        bitBuffer = bitBuffer | (bits << bitCount); // 10101010 << 4 = 10101010000 
                                                    //10101010000 | 00001111 = 10101010011
        
        writeByte(bitBuffer); //write a formed byte 1010011
            
        bits = bits >> (8  - bitCount); // shifting for 'clearing' bits that were written
                                    // 10101010011 >> 4 = 000010101010011
        
        lenght -= 8 - bitCount; //to keep track of the remaining bits left to write.

        resetBuffer();
    }
    while(lenght > 0){
        if(lenght >= 8){ // 1 byte or more left
            writeByte(bits);
            bits >>= 8; // remove the bits that are already in file
            lenght -= 8; 
        }
        else{ // if less than a byte is left
        //add whats left to buffer
            std::cout << "left std" << std::endl;
            bitCount = lenght; 
            bitBuffer = bits;
            lenght = 0; // reset to end the while loop
        }
    }
}

void BitPacker::writeByte(uint32_t byte) {
    // takes the least significant 8 bits (LSB) of bitBuffer
    //  byte = 10101010011, then takes 01001011
    outputFile.put(static_cast<char>(byte));
}

void BitPacker::writeLast() {
    uint32_t bits = 0; 
    std::cout << bitCount << std::endl;
    if(bitCount > 0) { // If there are bits in the buffer left from last time
        bitBuffer = bitBuffer | bits;
        // int paddingBits = 8 - bitCount; // Calculate the number of padding bits needed to complete a byte
        // bitBuffer = bitBuffer << paddingBits; // Left-shift the buffer to align the remaining bits to the left

        writeByte(bitBuffer); // Write the padded bits as a byte to the file
        // bits = bits >> (8  - bitCount);
        // bitCount -= 8; 
    }
}
void BitPacker::closeStream(){
    outputFile.put(EOF); 
    outputFile.close();
}
