#pragma once
#include "PEStructs.h"
#include <iostream>

void printDosHeader(const IMAGE_DOS_HEADER& header);
void printNtHeader(const IMAGE_NT_HEADERS64& header);
void printOptionalHeader(const IMAGE_OPTIONAL_HEADER64& header);
void printDataDirectories(const IMAGE_OPTIONAL_HEADER64& header);
void printSectionTable(const IMAGE_SECTION_HEADER* sections, uint16_t count);
void printImportTable(std::istream& file, const IMAGE_OPTIONAL_HEADER64& optionalHeader, const IMAGE_SECTION_HEADER* sections, uint16_t sectionCount);
void printExportTable(std::istream& file, const IMAGE_OPTIONAL_HEADER64& optionalHeader, const IMAGE_SECTION_HEADER* sections, uint16_t sectionCount); 