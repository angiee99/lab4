#include "archiver.h"
#include <iostream>

int main(int argc, char* argv[]) {
    
    try{
        if (argc < 3) {
            std::cout <<"To little arguments. Enter at the mode and the file\n";
            std::cout << "Usage: " << argv[0] << " --compress [outputFile] [inputFile]\n       "
            << argv[0] << " --decompress [inputFile]\n";
            return 1;
        }
        
        std::string mode = argv[1];
        std::string outputFile = argv[2];
        if(mode != "--compress" && mode != "--decompress"){
            std::cout <<"The mode is either ----compress or --decompress\n";
            std::cout << "Usage: " << argv[0] << " --compress [outputFile] [inputFile]\n       "
            << argv[0] << " --decompress [inputFile]\n";
            return 1;
        }

        Archiver LZW_Arch; 
        if (mode == "--compress") { 

            LZW_Arch.compress(argv[3], outputFile);

        }else if (mode == "--decompress") {

            LZW_Arch.decompress(outputFile);
        }
        
    }
    catch (std::invalid_argument &e){
        std::cout <<  e.what() << std::endl; 
    }
    catch(std::runtime_error &e){
        std::cout << e.what() << std::endl; 
    }
    catch(std::exception &e){
        std::cout <<  e.what() << std::endl; 
    }
    return 0;
}