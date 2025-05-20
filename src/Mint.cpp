#include <iostream>
#include <string.h>

int main(int argc, char* argv[]) {
    // parsing args  
    for (int i=1; i<argc; i++) {
        char* arg = argv[i];
        if (strcmp("install", arg) == 0) {
            std::cout << "xd install \n";
        }
    } 
}