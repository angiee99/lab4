#include "dictionary.h"
#include <iostream>

void testDict(){
    Dictionary dict; 
    dict.addCode("ca"); 
    dict.addCode("abb"); 
    std::cout << dict.getCode("ca")<< std::endl;
    std::cout << dict.getCode("a")<< std::endl;
    std::cout << dict.getCode("abb")<< std::endl;
    
    std::cout << dict.getString(205)<< std::endl;
    std::cout <<dict.getString(256)<< std::endl;
}