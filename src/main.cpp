#include <iostream>
#include <string>
#include "FileReader.h"
#include "DOSHeader.h"
#include "PEParser.h"

#define NOTEPAD_PATH "/mnt/c/Windows/System32/notepad.exe"

int main(int argc, char* argv[]) {
    const char* filePath = NOTEPAD_PATH;
    
    // Allow command line override of file path
    if (argc > 1) {
        filePath = argv[1];
    }

    FILE* f = fopen(filePath, "rb");
    if (!f) { 
        std::cerr << "Error opening file: " << filePath << std::endl;
        perror("fopen"); 
        return 1; 
    }

    // Read DOS header
    IMAGE_DOS_HEADER dosHeader;
    if (!FileReader::readHeader(f, &dosHeader, sizeof(IMAGE_DOS_HEADER))) {
        std::cerr << "Error reading DOS header" << std::endl;
        perror("fread");
        fclose(f);
        return 1;
    }

    // Verify DOS header magic number
    if (dosHeader.e_magic != 0x5A4D) { // "MZ" in little-endian
        std::cerr << "Invalid DOS header magic number" << std::endl;
        fclose(f);
        return 1;
    }

    printDosHeader(dosHeader);

    // Read NT header
    IMAGE_NT_HEADERS32 ntHeader;
    if (!FileReader::readHeader(f, &ntHeader, sizeof(IMAGE_NT_HEADERS32), dosHeader.e_lfanew)) {
        std::cerr << "Error reading NT header" << std::endl;
        perror("fread");
        fclose(f);
        return 1;
    }

    // Verify NT header signature
    if (ntHeader.Signature != 0x00004550) { // "PE\0\0" in little-endian
        std::cerr << "Invalid NT header signature" << std::endl;
        fclose(f);
        return 1;
    }

    printNtHeader(ntHeader);

    fclose(f);
    return 0;
}