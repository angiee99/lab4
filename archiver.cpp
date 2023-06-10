#include "archiver.h"
//#include "fileValidator.h"

void Archiver::compress(const std::string& inputFile, const std::string& outputFile) {

    validator.validateInput("input.txt"); 
    validator.validateCompressedFile("output.my");
    
    std::cout << "Compressing file " << inputFile ; 

    // mb here  create the output name for compressed file 
    this->encoder.encode(inputFile, outputFile);    

    std::cout << "... Done.\n";
}

void Archiver::decompress(const std::string& inputFile) {
    validator.validateCompressedFile("output.myzip", true);
    
    std::cout << "Getting out "<< inputFile;
// create the output name for decompressed file

    this->decoder.decode(inputFile, "output"); //!!! change the name

    std::cout << "... Done.\n";
}


