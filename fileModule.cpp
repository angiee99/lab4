#include "fileModule.h"
void FileValidator::validateInput(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        inputFile.close();
        throw std::runtime_error("Cannot open file: " + filename +" \n");
    }

    inputFile.close();
}
void FileValidator::validateOutput(const std::string& filename) {

    std::ofstream outputFile(filename);
    if (!outputFile) {
        outputFile.close();
        throw std::runtime_error("Cannot open file: " + filename +" \n");
    }

    outputFile.close();
}

void CompressedFileValidator::validateCompressedFile(const std::string& filename, bool isInput){
    if (isInput) validateInput(filename); 
    else validateOutput(filename);
    // validate the extension
        // Find the position of the dot (.) in the filename
    std::size_t dotPosition = filename.find_last_of('.');
    
    if (dotPosition == std::string::npos) {
        throw std::invalid_argument("in filename " + filename +
                                " there is no extension .myzip\n");
    }
        // Extract the file extension
    std::string fileExtension = filename.substr(dotPosition + 1);

        // Compare the extracted extension with the provided extension
        
    if (fileExtension != "myzip"){
        throw std::invalid_argument("in filename " + filename + 
        " there is incorrect extension " + fileExtension +", (must be .myzip)\n");
    }
}
