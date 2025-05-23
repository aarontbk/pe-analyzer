#pragma once
#include "PEStructs.h"
#include "FileReader.h"
#include <string>

class PEFile {
public:
    PEFile(const char* filePath);
    ~PEFile();

    bool isValid() const { return m_file != nullptr; }
    const std::string& getErrorMessage() const { return m_errorMessage; }
    
    bool parse();
    void printHeaders() const;

private:
    FILE* m_file;
    std::string m_errorMessage;
    IMAGE_DOS_HEADER m_dosHeader;
    IMAGE_NT_HEADERS32 m_ntHeader;
    bool m_isParsed;

    bool validateDosHeader();
    bool validateNtHeader();
}; 