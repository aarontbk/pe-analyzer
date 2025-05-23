#include "PEParser.h"
#include <iomanip>
#include <ctime>
#include <string>

void printDosHeader(const IMAGE_DOS_HEADER& header) {
    std::cout << "=== DOS Header ===" << std::endl;
    std::cout << std::left << std::setw(20) << "Magic number" << ": " 
              << (char)(header.e_magic & 0xFF) 
              << (char)(header.e_magic >> 8) << std::endl;
    std::cout << std::left << std::setw(20) << "e_lfanew (PE offset)" << ": " 
              << std::hex << std::setw(8) << std::setfill(' ') << (uint32_t)header.e_lfanew << std::endl;
}

void printNtHeader(const IMAGE_NT_HEADERS64& header) {
    std::cout << "\n=== NT Headers ===" << std::endl;
    std::cout << std::left << std::setw(20) << "Signature" << ": " 
              << (char)(header.Signature & 0xFF)
              << (char)((header.Signature >> 8) & 0xFF)
              << (char)((header.Signature >> 16) & 0xFF)
              << (char)((header.Signature >> 24) & 0xFF) << std::endl;
    
    // Machine type description
    std::string machineDesc;
    switch (header.FileHeader.Machine) {
        case 0x014c: machineDesc = " (x86)"; break;
        case 0x0200: machineDesc = " (Intel Itanium)"; break;
        case 0x8664: machineDesc = " (AMD64)"; break;
        default: machineDesc = " (Unknown)"; break;
    }
    
    std::cout << std::left << std::setw(20) << "Machine" << ": " 
              << std::hex << std::setw(4) << std::setfill(' ') << header.FileHeader.Machine 
              << machineDesc << std::endl;
    
    std::cout << std::left << std::setw(20) << "Number of Sections" << ": " 
              << std::dec << header.FileHeader.NumberOfSections << std::endl;
    
    // TimeDateStamp with UTC time
    std::cout << std::left << std::setw(20) << "TimeDateStamp" << ": " 
              << std::hex << std::setw(8) << std::setfill(' ') << header.FileHeader.TimeDateStamp;
    
    time_t timestamp = header.FileHeader.TimeDateStamp;
    char timeStr[100];
    std::tm* tm = std::gmtime(&timestamp);  // Use UTC time
    if (tm) {
        std::strftime(timeStr, sizeof(timeStr), " (%Y-%m-%d %H:%M:%S UTC)", tm);
        std::cout << timeStr;
    }
    std::cout << std::endl;
    
    std::cout << std::left << std::setw(20) << "SizeOfOptionalHeader" << ": " 
              << std::hex << std::setw(4) << std::setfill(' ') << header.FileHeader.SizeOfOptionalHeader << std::endl;
    
    // Characteristics description
    std::string charDesc;
    if (header.FileHeader.Characteristics & 0x0002) charDesc += "Executable, ";
    if (header.FileHeader.Characteristics & 0x0100) charDesc += "32-bit, ";
    if (header.FileHeader.Characteristics & 0x0020) charDesc += "64-bit, ";
    if (header.FileHeader.Characteristics & 0x2000) charDesc += "DLL, ";
    if (!charDesc.empty()) {
        charDesc = " (" + charDesc.substr(0, charDesc.length() - 2) + ")";
    }
    
    std::cout << std::left << std::setw(20) << "Characteristics" << ": " 
              << std::hex << std::setw(4) << std::setfill(' ') << header.FileHeader.Characteristics 
              << charDesc << std::endl;
}

void printDataDirectories(const IMAGE_OPTIONAL_HEADER64& header) {
    std::cout << "\n=== Data Directories ===" << std::endl;
    
    const char* directoryNames[] = {
        "[00] Export Table",
        "[01] Import Table",
        "[02] Resource Table",
        "[03] Exception Table",
        "[04] Certificate Table",
        "[05] Base Relocation Table",
        "[06] Debug",
        "[07] Architecture",
        "[08] Global Ptr",
        "[09] TLS Table",
        "[10] Load Config Table",
        "[11] Bound Import",
        "[12] Import Address Table",
        "[13] Delay Import Descriptor",
        "[14] CLR Header",
        "[15] Reserved"
    };

    for (int i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++) {
        const IMAGE_DATA_DIRECTORY& dir = header.DataDirectory[i];
        std::cout << std::left << std::setw(32) << directoryNames[i] << ": "
                  << "RVA: " << std::hex << std::setw(8) << std::setfill(' ') << dir.VirtualAddress
                  << " Size: " << std::setw(12) << std::setfill(' ') << dir.Size << std::endl;
    }
}

void printOptionalHeader(const IMAGE_OPTIONAL_HEADER64& header) {
    std::cout << "\n=== Optional Header (PE32+) ===" << std::endl;
    
    // Magic number description
    std::string magicDesc;
    switch (header.Magic) {
        case 0x10b: magicDesc = " (PE32)"; break;
        case 0x20b: magicDesc = " (PE32+)"; break;
        case 0x107: magicDesc = " (ROM)"; break;
        default: magicDesc = " (Unknown)"; break;
    }
    
    std::cout << std::left << std::setw(20) << "Magic" << ": " 
              << std::hex << std::setw(3) << std::setfill(' ') << header.Magic 
              << magicDesc << std::endl;
    
    std::cout << std::left << std::setw(20) << "Entry Point" << ": " 
              << std::hex << std::setw(8) << std::setfill(' ') << header.AddressOfEntryPoint << std::endl;
    
    std::cout << std::left << std::setw(20) << "Image Base" << ": " 
              << std::hex << std::setw(16) << std::setfill(' ') << header.ImageBase << std::endl;
    
    std::cout << std::left << std::setw(20) << "Section Alignment" << ": " 
              << std::hex << std::setw(8) << std::setfill(' ') << header.SectionAlignment << std::endl;
    
    std::cout << std::left << std::setw(20) << "File Alignment" << ": " 
              << std::hex << std::setw(8) << std::setfill(' ') << header.FileAlignment << std::endl;
    
    // Subsystem description
    std::string subsystemDesc;
    switch (header.Subsystem) {
        case 0: subsystemDesc = " (Unknown)"; break;
        case 1: subsystemDesc = " (Native)"; break;
        case 2: subsystemDesc = " (Windows GUI)"; break;
        case 3: subsystemDesc = " (Windows CUI)"; break;
        case 5: subsystemDesc = " (OS/2 CUI)"; break;
        case 7: subsystemDesc = " (POSIX CUI)"; break;
        case 9: subsystemDesc = " (Windows CE GUI)"; break;
        case 10: subsystemDesc = " (EFI Application)"; break;
        case 11: subsystemDesc = " (EFI Boot Service Driver)"; break;
        case 12: subsystemDesc = " (EFI Runtime Driver)"; break;
        case 13: subsystemDesc = " (EFI ROM)"; break;
        case 14: subsystemDesc = " (XBOX)"; break;
        case 16: subsystemDesc = " (Windows Boot Application)"; break;
        default: subsystemDesc = " (Unknown)"; break;
    }
    
    std::cout << std::left << std::setw(20) << "Subsystem" << ": " 
              << std::hex << std::setw(4) << std::setfill(' ') << header.Subsystem 
              << subsystemDesc << std::endl;
    
    // DLL Characteristics description
    std::string dllCharDesc;
    if (header.DllCharacteristics & 0x0020) dllCharDesc += "High Entropy VA, ";
    if (header.DllCharacteristics & 0x0040) dllCharDesc += "Dynamic Base, ";
    if (header.DllCharacteristics & 0x0080) dllCharDesc += "Force Integrity, ";
    if (header.DllCharacteristics & 0x0100) dllCharDesc += "NX compatible, ";
    if (header.DllCharacteristics & 0x0200) dllCharDesc += "No Isolation, ";
    if (header.DllCharacteristics & 0x0400) dllCharDesc += "No SEH, ";
    if (header.DllCharacteristics & 0x0800) dllCharDesc += "No Bind, ";
    if (header.DllCharacteristics & 0x1000) dllCharDesc += "AppContainer, ";
    if (header.DllCharacteristics & 0x2000) dllCharDesc += "WDM Driver, ";
    if (header.DllCharacteristics & 0x4000) dllCharDesc += "Control Flow Guard, ";
    if (header.DllCharacteristics & 0x8000) dllCharDesc += "Terminal Server aware, ";
    if (!dllCharDesc.empty()) {
        dllCharDesc = " (" + dllCharDesc.substr(0, dllCharDesc.length() - 2) + ")";
    }
    
    std::cout << std::left << std::setw(20) << "DLL Characteristics" << ": " 
              << std::hex << std::setw(4) << std::setfill(' ') << header.DllCharacteristics 
              << dllCharDesc << std::endl;
    
    std::cout << std::left << std::setw(20) << "Size of Image" << ": " 
              << std::hex << std::setw(8) << std::setfill(' ') << header.SizeOfImage << std::endl;
    
    std::cout << std::left << std::setw(20) << "Size of Headers" << ": " 
              << std::hex << std::setw(8) << std::setfill(' ') << header.SizeOfHeaders << std::endl;

    // Print data directories after the optional header
    printDataDirectories(header);
}

std::string getSectionFlagsDescription(uint32_t flags) {
    std::string desc;
    if (flags & IMAGE_SCN_CNT_CODE) desc += "Code, ";
    if (flags & IMAGE_SCN_CNT_INITIALIZED_DATA) desc += "Initialized Data, ";
    if (flags & IMAGE_SCN_CNT_UNINITIALIZED_DATA) desc += "Uninitialized Data, ";
    if (flags & IMAGE_SCN_MEM_EXECUTE) desc += "Execute, ";
    if (flags & IMAGE_SCN_MEM_READ) desc += "Read, ";
    if (flags & IMAGE_SCN_MEM_WRITE) desc += "Write, ";
    
    if (!desc.empty()) {
        desc = " (" + desc.substr(0, desc.length() - 2) + ")";
    }
    return desc;
}

void printSectionTable(const IMAGE_SECTION_HEADER* sections, uint16_t count) {
    std::cout << "\n=== Section Table ===" << std::endl;
    
    for (uint16_t i = 0; i < count; i++) {
        const IMAGE_SECTION_HEADER& section = sections[i];
        
        // Print section name with index
        std::cout << "[" << i << "] ";
        std::string name(section.Name, 8);
        name = name.substr(0, name.find('\0'));  // Trim null terminator
        std::cout << name << std::endl;
        
        // Print section details with proper indentation
        std::cout << "    RVA       : " << std::hex << std::setw(8) << std::setfill(' ') 
                  << section.VirtualAddress << std::endl;
        std::cout << "    RawOffset : " << std::setw(8) << std::setfill(' ') 
                  << section.PointerToRawData << std::endl;
        std::cout << "    VirtualSize : " << std::setw(8) << std::setfill(' ') 
                  << section.Misc.VirtualSize << std::endl;
        std::cout << "    RawSize     : " << std::setw(8) << std::setfill(' ') 
                  << section.SizeOfRawData << std::endl;
        std::cout << "    Flags       : " << std::setw(8) << std::setfill(' ') 
                  << section.Characteristics 
                  << getSectionFlagsDescription(section.Characteristics) << std::endl;
        
        std::cout << std::endl;  // Add blank line between sections
    }
} 