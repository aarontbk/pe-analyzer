#include "PEParser.h"

void printDosHeader(const IMAGE_DOS_HEADER& header) {
    std::cout << "=== DOS Header ===" << std::endl;
    std::cout << "Magic number: " << (char)(header.e_magic & 0xFF) 
              << (char)(header.e_magic >> 8) << std::endl;
    std::cout << "Offset to NT header: 0x" << std::hex << header.e_lfanew << std::endl;
}

void printNtHeader(const IMAGE_NT_HEADERS32& header) {
    std::cout << "\n=== NT Header ===" << std::endl;
    std::cout << "Signature: " << (char)(header.Signature & 0xFF)
              << (char)((header.Signature >> 8) & 0xFF)
              << (char)((header.Signature >> 16) & 0xFF)
              << (char)((header.Signature >> 24) & 0xFF) << std::endl;
    std::cout << "Machine: 0x" << std::hex << header.FileHeader.Machine << std::endl;
    std::cout << "Number of sections: " << std::dec << header.FileHeader.NumberOfSections << std::endl;
    std::cout << "Characteristics: 0x" << std::hex << header.FileHeader.Characteristics << std::endl;
} 