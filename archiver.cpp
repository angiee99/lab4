#include "archiver.h"

void Archiver::compress(const std::string& inputFile, const std::string& outputFile) {

    validator.validateInput(inputFile); 
    validator.validateCompressedFile(outputFile);
    
    std::cout << "Compressing file " << inputFile << " to " << outputFile; 

    encoder.encode(inputFile, outputFile);    

    std::cout << "... Done.\n";
}

void Archiver::decompress(const std::string& inputFile) {
    validator.validateCompressedFile(inputFile, true);
    
    std::cout << "Getting out "<< inputFile;

    decoder.decode(inputFile);

    std::cout << "... Done.\n";
}


