// #include "archiver.h"
#include "dictionary.h"
#include "archiver.h"

#include <iostream>
int main(int argc, char* argv[]) {
    try{
        
        Archiver LZW_Arch; 
    
        LZW_Arch.compress("input.txt", "output.bmp");

        LZW_Arch.decompress("output.bmp");
    
    }
    catch (std::invalid_argument &e){
        e.what(); 
    }
    catch(std::runtime_error &e){
        e.what();
    }
    catch(std::exception &e){
        e.what();
    }
    return 0;
}