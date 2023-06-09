#include "Encoder.h" 

void Encoder::encode(const std::string& inputFilePath, const std::string& outputFilePath) {

    // fileReader (or Validator)
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Failed to open input file: " + inputFilePath);
    }
    // fileReader (or Validator)

    // FileWriter fileWriter(outputFilePath);

    char currentChar;
    std::string currentStr ="";

    while (inputFile.get(currentChar)) {
        currentStr += currentChar;
        std::cout << currentStr << std::endl;

        if (!dictionary.includes(currentStr)) {
                // without the last char
            currentStr = currentStr.substr(0, currentStr.length() - 1);

            //output    
                // represents the encoded representation of the previous sequence.
            packCode(dictionary.getCode(currentStr)); 
            
            //dict entry 
                // add to dictionary including the current character
            dictionary.addCode(currentStr+currentChar); 
            
            
            currentStr = currentChar; //currentStr = last char added
            
            if (dictionary.isFull()) { //
                dictionary.clear();
                currentStr = "";
            }
        }
    }

    // Process the last character sequence
    if (!currentStr.empty()) {
        packCode(dictionary.getCode(currentStr));
    }
    writer.closeStream();
    // Close the output file
    // fileWriter.close();
};

void Encoder::packCode(uint32_t code) {
        // pass the current bit-size of code (9-..)
    writer.writeBits(code, sizeof(code), dictionary.getCurrentSize()); 

}
    