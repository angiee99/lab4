// #include "archiver.h"
#include "dictionary.h"
#include "Encoder.h"
#include <iostream>
int main(int argc, char* argv[]) {
    Encoder encoder; 
    encoder.encode("input.txt", "output.bmp");
    
    // if (argc < 4) {
    //     std::cout << "Usage: " << argv[0] << " [--compress/--decompress] [outputFile] [inputFiles...]\n";
    //     return 1;
    // }

    // std::string mode = argv[1];
    // std::string outputFile = argv[2];

    // if (mode == "--compress") {
    //     for (int i = 3; i < argc; i++) {
    //         Archiver::compress(argv[i], outputFile);
    //     }
    // } else if (mode == "--decompress") {
    //     Archiver::decompress(outputFile);
    // } else {
    //     std::cout << "Invalid mode.\n";
    //     return 1;
    // }

    return 0;
}