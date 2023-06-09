#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>

#include "dictionary.h"
#include "fileModule.h"
#include "BitReader.h"

class Decoder {
private:
    Dictionary dictionary;
    BitReader reader;
    std::ofstream outputFile;

public:
    void decode(const std::string& inputFilePath, const std::string& outputFilePath) {
       
        // std::ifstream inputFile(inputFilePath, std::ios::binary);
        // if (!inputFile) {
        //     throw std::runtime_error("Failed to open input file: " + inputFilePath);
        // }

        outputFile.open(outputFilePath);// std::ios::binary
        if (!outputFile) {
            throw std::runtime_error("Failed to open output file: " + outputFilePath);
        }

        reader.setStream(inputFilePath);

        uint32_t prevCode, curCode;
        std::string entry;
        char ch;

        prevCode = reader.readCode();
        std::cout << "prevCode: " << prevCode << std::endl;
        output(entryFromCode(prevCode));

        while (reader.hasData()) {
            curCode = reader.readCode();
            entry = entryFromCode(curCode);
            output(entry);

            ch = entry[0];
            dictionary.addCode(entryFromCode(prevCode) + ch);
            prevCode = curCode;
        }
        reader.closeStream();
        // inputFile.close();
        outputFile.close();
    }

private:
    std::string entryFromCode(uint32_t code) {
        if (code < dictionary.getCurrentSize()) {
            std::cout << dictionary.getString(code) << std::endl;
            return dictionary.getString(code);
        } else {
            std::string entry = dictionary.getString(code - 1);
            entry += entry[0];
            std::cout << entry << std::endl;
            return entry;
        }
    }

    void output(const std::string& entry) {
    //     outputFile.write(entry.c_str(), entry.length());
        outputFile << entry; 
    }
};