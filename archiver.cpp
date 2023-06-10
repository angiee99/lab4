#include "archiver.h"
//#include "fileValidator.h"



void Archiver::compress(const std::string& inputFile, const std::string& outputFile) {

    validator.validateInput(inputFile); 
    validator.validateCompressedFile(outputFile);
    
    std::cout << "Compressing file " << inputFile ; 

    this->encoder.encode(inputFile, outputFile);    

    std::cout << "... Done.\n";
}

void Archiver::decompress(const std::string& inputFile) {
    validator.validateCompressedFile(inputFile, true);
    
    std::cout << "Getting out "<< inputFile;

    this->decoder.decode(inputFile);

    std::cout << "... Done.\n";
}


