#pragma once

#include <fstream>
#include <stdexcept>
#include <vector>

class FileWriter{
    private:
    std::ofstream outputFile;
public:
    FileWriter(const std::string& filePath) : outputFile(filePath, std::ios::binary) {
        if (!outputFile) {
            throw std::runtime_error("Failed to open output file: " + filePath);
        }
    }
    ~FileWriter(){
        outputFile.close();
    }
    void writeByte(uint8_t byte) {
        outputFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
    }

    void writeBytes(const std::vector<uint32_t>& bytes) {
        outputFile.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    }
};