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
void Decoder::decode(const std::string& inputFilePath, const std::string& outputFilePath) {
    
    outputFile.open(outputFilePath);// std::ios::binary
    if (!outputFile) {
        throw std::invalid_argument("Failed to open output file: " + outputFilePath);
    }

    reader.setStream(inputFilePath);

    uint32_t prevCode, curCode;
    std::string entry;
    char ch;

// reading first code
    prevCode = reader.readCode(dictionary.getCurrentSize());
    std::cout << "prevCode: " << prevCode << std::endl;
    output(entryFromCode(prevCode));
//
    while (reader.hasData()) {
        curCode = reader.readCode(dictionary.getCurrentSize()); // get current
        std::cout << "curCode: "  << curCode << std::endl; 
        
        if (!reader.hasData() || curCode > dictionary.getNextCode()) 
        {  // do not write the EOF or dont check for curCode that is out of dict
            break; 
        }

        if ( curCode == dictionary.getNextCode() - 1){ // special case
            std::cout << "prevCode" << prevCode << std::endl;
            std::cout << "curCode: "<< curCode << std::endl;
            dictionary.addCode(entryFromCode(prevCode) + entryFromCode(prevCode)[0]);
        }
        else{
            entry = entryFromCode(curCode); // form output (if <= 255 -> output, 
                                                //else look up for decode)
            // output(entry); // output it

            ch = entry[0]; //first "part" of entry (current code value)
            if(ch)
            dictionary.addCode(entryFromCode(prevCode) + ch); // add prev + entry[0] to dict
        }
        entry = entryFromCode(curCode);
        output(entry);
        prevCode = curCode; // reset previous
    }
    // output(entryFromCode(prevCode));
    reader.closeStream();
    outputFile.close();
}


std::string Decoder::entryFromCode(uint32_t code) {
    if (code <= 255) { // if basic ascii value: just return it 
            // std::cout << dictionary.getString(code) << std::endl;
        std::string result(1, (char)(code)); 
        return result;
        // return dictionary.getString(code);
    } else { // if not basic value, search for it in the table
        std::string entry = dictionary.getString(code);
        //  entry += entry[0]; //??
            // std::cout << entry << std::endl;
        return entry;
    }
}

void Decoder::output(const std::string& entry) {
//     outputFile.write(entry.c_str(), entry.length());
    outputFile << entry; 
}