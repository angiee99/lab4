
#include "dictionary.h"
#include "archiver.h"
// #include "fileModule.h"

#include <iostream>
int main(int argc, char* argv[]) {
    // ./code --compress output.mgzip input.bmp
    //  ./code --decompress output.mgzip
    // OR ./code --compress input.bmp
    
    try{
        if (argc < 3) {
            std::cout << "Usage: " << argv[0] << " [--compress [outputFile] [inputFile]\n"
            << " [--decompress [inputFile]\n";
            return 1;
        }

        
        std::string mode = argv[1];
        std::string outputFile = argv[2];
        if(mode != "--compress" && mode != "--decompress"){
            std::cout << "Usage: " << argv[0] << " [--compress [outputFile] [inputFile]\n"
            << " [--decompress [inputFile]\n";
            return 1;
        }

            // if mode is not ok -> "Invalid mode" ->  return 2
        Archiver LZW_Arch; 
        if (mode == "--compress") {
            
                LZW_Arch.compress(argv[3], outputFile);

        } else if (mode == "--decompress") {
            LZW_Arch.decompress(outputFile);
        }
        
            // Archiver LZW_Arch; 
        
            // LZW_Arch.compress("aba.txt", "output.myzip");

            // LZW_Arch.decompress("output.myzip");
        
    }
    catch (std::invalid_argument &e){
        std::cout <<  e.what(); 
    }
    catch(std::runtime_error &e){
        std::cout << e.what();
    }
    catch(std::exception &e){
        std::cout <<  e.what();
    }
    return 0;
}