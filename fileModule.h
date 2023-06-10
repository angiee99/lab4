#pragma once

#include <fstream>
#include <stdexcept>
#include <vector>

class FileValidator{
public:
    void validateInput(const std::string& filename);
    void validateOutput(const std::string& filename);
}; 

class CompressedFileValidator: public FileValidator{
public:
    void validateCompressedFile(const std::string& filename, bool isInput = false);
};

class FileNameFactory{
    // nameOutput
    // recoverInputName
};