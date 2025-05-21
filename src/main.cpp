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
#pragma pack(pop)

int main() {
    FILE* f = fopen(NOTEPAD_PATH, "rb");
    if (!f) { perror("fopen"); return 1; }

    // Read the DOS header
    IMAGE_DOS_HEADER dosHeader;
    if (fread(&dosHeader, sizeof(IMAGE_DOS_HEADER), 1, f) != 1) {
        perror("fread");
        fclose(f);
        return 1;
    }

    // Print the magic number (Little Endian)
    std::cout << "Magic number: " << (char)(dosHeader.e_magic & 0xFF) 
              << (char)(dosHeader.e_magic >> 8) << std::endl;
    
    // Print the offset to NT header
    std::cout << "Offset to NT header: 0x" << std::hex << dosHeader.e_lfanew << std::endl;

    fclose(f);
    return 0;
}