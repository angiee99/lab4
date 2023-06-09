#include "archiver.h"
//#include "fileValidator.h"

void Archiver::compress(const std::string& inputFile, const std::string& outputFile) {
    // mb here validate the input and output files 
    this->encoder.encode(inputFile, outputFile);    

    std::cout << "Compressing file " << inputFile << "... Done.\n";
}

void Archiver::decompress(const std::string& inputFile) {

// varifying the input file for decompression
    // std::string outputPrefix = inputFile.substr(0, inputFile.find_last_of('.'));

    this->decoder.decode(inputFile, "output"); //!!! change the name

    std::cout << "Getting out "<< inputFile << std::endl;
}


