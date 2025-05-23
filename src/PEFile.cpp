#include "PEFile.h"
#include "PEParser.h"
#include <iostream>

PEFile::PEFile(const char* filePath) : m_file(nullptr), m_isParsed(false) {
    m_file = FileReader::openFile(filePath, m_errorMessage);
}

PEFile::~PEFile() {
    FileReader::closeFile(m_file);
}

bool PEFile::parse() {
    if (!m_file) {
        return false;
    }

    // Read DOS header
    if (!FileReader::readHeader(m_file, &m_dosHeader, sizeof(IMAGE_DOS_HEADER))) {
        m_errorMessage = "Error reading DOS header";
        perror("fread");
        return false;
    }

    if (!validateDosHeader()) {
        return false;
    }

    // Read NT header
    if (!FileReader::readHeader(m_file, &m_ntHeader, sizeof(IMAGE_NT_HEADERS32), m_dosHeader.e_lfanew)) {
        m_errorMessage = "Error reading NT header";
        perror("fread");
        return false;
    }

    if (!validateNtHeader()) {
        return false;
    }

    m_isParsed = true;
    return true;
}

void PEFile::printHeaders() const {
    if (!m_isParsed) {
        std::cerr << "No headers to print - file not parsed" << std::endl;
        return;
    }

    printDosHeader(m_dosHeader);
    printNtHeader(m_ntHeader);
}

bool PEFile::validateDosHeader() {
    if (m_dosHeader.e_magic != 0x5A4D) { // "MZ" in little-endian
        m_errorMessage = "Invalid DOS header magic number";
        return false;
    }
    return true;
}

bool PEFile::validateNtHeader() {
    if (m_ntHeader.Signature != 0x00004550) { // "PE\0\0" in little-endian
        m_errorMessage = "Invalid NT header signature";
        return false;
    }
    return true;
} 