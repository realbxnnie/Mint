#include <iostream>
#include <cstring>
#include <vector>
#include "Mint.h"

int main(int argc, char* argv[]) {
    // Parsing arguments
    for (int i=0;i<argc;i++) {
        char* arg = argv[i];
        if (strcmp("--yes", arg)==0 || strcmp("-y", arg)==0) {
            mintAskOnPkgOperation=false;
        } 
    }

        
    // Parsing commands
    for (int i=0;i<argc;i++) {
        char* cmd = argv[i];
        if (strcmp("install", cmd)==0) {
            // Install packages
            std::vector<std::string> packages = {};

            if (argv[i+1]==nullptr) { Mint::Usage(); }
            while (argv[i+1] != nullptr && !strprf("-", argv[i+1]) && argv[i+1]) {
                packages.push_back(argv[i+1]);
                i++;
            }
            Mint::Install(packages);
        } 
        else if (strcmp("update", cmd)==0) {
            Mint::Update();
        } 
        else if (strcmp("purge", cmd)==0) {
            // Remove packages
            std::vector<std::string> packages = {};

            if (argv[i+1]==nullptr) { Mint::Usage(); }
            while (argv[i+1] != nullptr && !strprf("-", argv[i+1]) && argv[i+1]) {
                packages.push_back(argv[i+1]);
                i++;
            }
            Mint::Remove(packages);
        } 
        else if (strcmp("list", cmd)==0) {
            Mint::List();
        }
        else if (strcmp("info", cmd)==0) {
            Mint::Info();
        }
        else if (strcmp("help", cmd)==0) {
            Mint::Usage();
        }
    }

    Mint::Usage();


    return 0;
}