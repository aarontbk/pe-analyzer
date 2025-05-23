#include <iostream>
#include <string>
#include "PEFile.h"

int main(int argc, char* argv[]) {
    const char* filePath;
    
    // Allow command line override of file path
    if (argc > 1) {
        filePath = argv[1];
    }

    PEFile peFile(filePath);
    if (!peFile.isValid()) {
        std::cerr << "Failed to open or parse PE file." << std::endl;
        return 1;
    }

    peFile.printHeaders();
    return 0;
}