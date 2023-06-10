/*
    initialize TABLE[0 to 255] = code for individual bytes
    CODE = read next code
    STRING = TABLE[CODE]
    output STRING
    while there are still codes to receive:
        CODE = read next code
        if TABLE[CODE] is not defined: // needed because sometimes the
            ENTRY = STRING + STRING[0] // decoder may not yet have entry else:
            ENTRY = TABLE[CODE] output ENTRY
            add STRING+ENTRY[0] to TABLE 
            STRING = ENTRY //reset
*/
#include "Decoder.h"
void Decoder::decode(const std::string& inputFilePath) {
    
    std::string outputName = reader.setStream(inputFilePath); //init the BitReader
    std::cout << "\n" << outputName <<std::endl;

    outputFile.open(outputName); // 
    if (!outputFile) {
        throw std::invalid_argument("Failed to open output file: " + outputName);
    }    
    
    uint32_t prevCode, curCode;
    std::string entry; //decoded string repr

   
// reading first code
    prevCode = reader.readCode(dictionary.getCurrentSize()); //just read it
    output(entryFromCode(prevCode)); //then output the string representation

// reading all codes while there are still some to read
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
            entry = entryFromCode(curCode); // form output sting from given code
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


std::string Decoder::entryFromCode(uint32_t code) {
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