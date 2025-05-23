#pragma once
#include "PEStructs.h"
#include <string>
#include <vector>
#include <fstream>

class PEFile {
public:
    PEFile(const std::string& filename);
    ~PEFile();

    bool isValid() const { return m_isValid; }
    void printHeaders() const;

private:
    bool readDosHeader();
    bool readNtHeader();
    bool readSectionHeaders();
    bool validateDosHeader() const;
    bool validateNtHeader() const;

    mutable std::ifstream m_file;
    bool m_isValid;
    IMAGE_DOS_HEADER m_dosHeader;
    IMAGE_NT_HEADERS64 m_ntHeader;
    std::vector<IMAGE_SECTION_HEADER> m_sectionHeaders;
}; 