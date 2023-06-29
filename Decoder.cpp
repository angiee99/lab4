#include "Decoder.h"

Decoder::~Decoder(){
    if(outputFile.is_open()) outputFile.close();
}
void Decoder::decode(const std::string& inputFilePath) {
    
    std::string outputName = reader.setStream(inputFilePath); //init the BitReader

    outputFile.open(outputName); 
    if (!outputFile) {
        throw std::invalid_argument("Failed to open output file: " + outputName);
    }    
    
    uint16_t prevCode, curCode;
    std::string entry; //decoded string repr

   
// reading first code
    prevCode = reader.readCode(dictionary.getCurrentSize()); //just read it
    output(entryFromCode(prevCode)); //then output the string representation

// reading all codes 
    while (reader.hasData()) {
        curCode = reader.readCode(dictionary.getCurrentSize()); // get current code
        
        if (!reader.hasData() || curCode > dictionary.getNextCode()) 
        {  // do not write the EOF and dont check for curCode that is out of dict
            break; 
        }

        if ( curCode == dictionary.getNextCode() - 1){ // special case cScSc, where c is a byte and S is a string 
            dictionary.addCode(entryFromCode(prevCode) + entryFromCode(prevCode)[0]);
        }
        else{
            entry = entryFromCode(curCode); // get sting from given code
            dictionary.addCode(entryFromCode(prevCode) + entry[0]); // add prev + entry[0] to dict
        }

        entry = entryFromCode(curCode);
        output(entry); //write to uncompressed file
        prevCode = curCode; // reset previous
    }
    //close the streams
    reader.closeStream(); 
    outputFile.close();
}


std::string Decoder::entryFromCode(uint16_t code) {
    if (code <= 255) { // if basic ascii value: just return its char 
        std::string result(1, (char)(code)); 
        return result;
    } else { // if not basic value, search for it in the table
        return dictionary.getString(code);
    }
}

void Decoder::output(const std::string& entry) {
    outputFile << entry; 
}