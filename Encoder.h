#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "dictionary.h"
#include "fileModule.h"
#include "BitWriter.h"

class Encoder {
private:
    Dictionary dictionary;
    std::vector<uint32_t> encodedData; //mb dont need
    BitWriter writer; 

   
public:
    void encode(const std::string& inputFilePath, const std::string& outputFilePath) {

    // fileReader (or Validator)
        std::ifstream inputFile(inputFilePath, std::ios::binary);
        if (!inputFile) {
            throw std::runtime_error("Failed to open input file: " + inputFilePath);
        }
    // fileReader (or Validator)

        FileWriter fileWriter(outputFilePath);

        char currentChar;
        std::string currentStr ="";
        
        while (inputFile.get(currentChar)) {
            currentStr += currentChar;
            std::cout << currentStr << std::endl;

            if (!dictionary.includes(currentStr)) {
                // without the last char
                currentStr = currentStr.substr(0, currentStr.length() - 1);
                   
                   // represents the encoded representation of the previous sequence.
                encodeCode(dictionary.getCode(currentStr)); 
                
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
            encodeCode(dictionary.getCode(currentStr));
        }

        // for(int i = 0; i < encodedData.size(); i++){
        //      std::cout << encodedData[i] << std::endl;
        // }
       
         // Flush any remaining bits in the BitWriter
        // writer.flushBuffer();

        // Write the packed bytes to the output file
        // fileWriter.writeBytes(writer.getPackedData());

        // Close the output file
        fileWriter.close();
    };
// can be void 
    void  encodeCode(uint32_t code) {
        writer.writeBits(code, sizeof(code), dictionary.getCurrentSize()); // pass the current bit-size of code (9-..)

        // encodedData.push_back(result);
    }
    
};