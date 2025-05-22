#include "DOSHeader.h"

void printDosHeader(const IMAGE_DOS_HEADER& header) {
    std::cout << "=== DOS Header ===" << std::endl;
    std::cout << "Magic number: " << (char)(header.e_magic & 0xFF) 
              << (char)(header.e_magic >> 8) << std::endl;
    std::cout << "Offset to NT header: 0x" << std::hex << header.e_lfanew << std::endl;
} 