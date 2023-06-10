#include "Encoder.h" 

void Encoder::encode(const std::string& inputFilePath, const std::string& outputFilePath) {

    inputFile.open(inputFilePath, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Failed to open input file: " + inputFilePath);
    }
    
    writer.initWriter(outputFilePath, inputFilePath); 
    char nextChar; //next 
    std::string currentStr =""; //curent sequence we are looking at
    while (inputFile.get(nextChar)) {
        
        currentStr += nextChar;

        if (!dictionary.includes(currentStr)) {
            // without the last char
            currentStr = currentStr.substr(0, currentStr.length() - 1);

            //output    
                // represents the encoded representation of the previous sequence.
            packCode(dictionary.getCode(currentStr)); 
            
            //dict entry 
                // add to dictionary including the current character
            dictionary.addCode(currentStr+nextChar); 
            
            
            currentStr = nextChar; //currentStr = last char added
            
            if (dictionary.isFull()) { //reset dictionary
                dictionary.clear();
                currentStr = "";
            }
        }
        
    }// Process the last character sequence with prev str now
    if (!currentStr.empty()) {
        packCode(dictionary.getCode(currentStr));
    }
    writer.writeLast();
    writer.closeStream(); // Close the output file
    inputFile.close();   //  Close the input file
};

void Encoder::packCode(uint16_t code) {
        // pass the current bit-size of code (9-..)
    writer.packBits(code, dictionary.getCurrentSize()); 
}
    