#include <iostream>
#include <cstdint>

#define NOTEPAD_PATH "./notepad.exe"

#pragma pack(push, 1)
struct IMAGE_DOS_HEADER {
    uint16_t e_magic;      // Magic number
    uint16_t e_cblp;       // Bytes on last page of file
    uint16_t e_cp;         // Pages in file
    uint16_t e_crlc;       // Relocations
    uint16_t e_cparhdr;    // Size of header in paragraphs
    uint16_t e_minalloc;   // Minimum extra paragraphs needed
    uint16_t e_maxalloc;   // Maximum extra paragraphs needed
    uint16_t e_ss;         // Initial (relative) SS value
    uint16_t e_sp;         // Initial SP value
    uint16_t e_csum;       // Checksum
    uint16_t e_ip;         // Initial IP value
    uint16_t e_cs;         // Initial (relative) CS value
    uint16_t e_lfarlc;     // File address of relocation table
    uint16_t e_ovno;       // Overlay number
    uint16_t e_res[4];     // Reserved words
    uint16_t e_oemid;      // OEM identifier
    uint16_t e_oeminfo;    // OEM information
    uint16_t e_res2[10];   // Reserved words
    int32_t  e_lfanew;     // File address of new exe header
};

struct IMAGE_FILE_HEADER {
    uint16_t Machine;
    uint16_t NumberOfSections;
    uint32_t TimeDateStamp;
    uint32_t PointerToSymbolTable;
    uint32_t NumberOfSymbols;
    uint16_t SizeOfOptionalHeader;
    uint16_t Characteristics;
};

struct IMAGE_NT_HEADERS32 {
    uint32_t Signature;      // "PE\0\0"
    IMAGE_FILE_HEADER FileHeader;
    // Optional header omitted for simplicity
};
#pragma pack(pop)

template<typename T>
bool readHeader(FILE* file, T& header, long offset = 0) {
    if (offset != 0) {
        if (fseek(file, offset, SEEK_SET) != 0) {
            return false;
        }
    }
    return fread(&header, sizeof(T), 1, file) == 1;
}

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

int main() {
    FILE* f = fopen(NOTEPAD_PATH, "rb");
    if (!f) { perror("fopen"); return 1; }

    // Read DOS header
    IMAGE_DOS_HEADER dosHeader;
    if (!readHeader(f, dosHeader)) {
        perror("fread");
        fclose(f);
        return 1;
    }
    printDosHeader(dosHeader);

    // Read NT header
    IMAGE_NT_HEADERS32 ntHeader;
    if (!readHeader(f, ntHeader, dosHeader.e_lfanew)) {
        perror("fread");
        fclose(f);
        return 1;
    }
    printNtHeader(ntHeader);

    fclose(f);
    return 0;
}