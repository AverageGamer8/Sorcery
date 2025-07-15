#include <iostream>
#include <string>

#include "game.h"
#include "player.h"

int main(int argc, char** argv) {
    std::cout << "start!" << std::endl;
    
    std::string deck1File;
    std::string deck2File;
    std::string initFile;

    for (int i = 1; i < argc; i++) {
        std::string curArg = argv[i];
        std::cout << curArg << std::endl;

        if (curArg == "-deck1") {
            ++i;
            if (i >= argc) {
                std::cerr << "Invalid deck1 specified!" << std::endl;
                return 1;
            }
            deck1File = argv[i];
        } else if (curArg == "-deck2") {
            ++i;
            if (i >= argc) {
                std::cerr << "Invalid deck2 specified!" << std::endl;
                return 1;
            }
            deck2File = argv[i];
        } else if (curArg == "-init") {
            ++i;
            if (i >= argc) {
                std::cerr << "Invalid init specified!" << std::endl;
                return 1;
            }
            initFile = argv[i];
        } else if (curArg == "-testing") {
            
        } else if (curArg == "-graphics") {
            
        } else {
            std::cerr << "Invalid argument " << curArg << "." << std::endl;
            return 1;
        }
    }
}