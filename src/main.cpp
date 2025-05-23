#include <iostream>
#include <string>
#include "PEFile.h"

#define NOTEPAD_PATH "/mnt/c/Windows/System32/notepad.exe"

int main(int argc, char* argv[]) {
    const char* filePath = NOTEPAD_PATH;
    
    // Allow command line override of file path
    if (argc > 1) {
        filePath = argv[1];
    }

    PEFile peFile(filePath);
    if (!peFile.isValid()) {
        std::cerr << peFile.getErrorMessage() << std::endl;
        return 1;
    }

    if (!peFile.parse()) {
        std::cerr << peFile.getErrorMessage() << std::endl;
        return 1;
    }

    peFile.printHeaders();
    return 0;
}