// #include "archiver.h"
#include "dictionary.h"
#include "Encoder.h"
#include "Decoder.h"

#include <iostream>
int main(int argc, char* argv[]) {
    Encoder encoder; 
    encoder.encode("input.txt", "output2.bmp");
    // Decoder decoder;
    // decoder.decode("output.bmp", "banana.txt");
  




    return 0;
}