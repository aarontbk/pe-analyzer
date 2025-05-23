#include <iostream>
#include <string>
#include "PEFile.h"

#define NOTEPAD_PATH "/mnt/c/Windows/System32/notepad.exe"
#define CHROME_PATH "/mnt/c/Program Files/Google/Chrome/Application/chrome.exe"

int main(int argc, char* argv[]) {
    const char* filePath = CHROME_PATH;
    
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