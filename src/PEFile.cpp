#include "PEFile.h"
#include "PEParser.h"
#include <iostream>

PEFile::PEFile(const std::string& filename) : m_isValid(false) {
    m_file.open(filename, std::ios::binary);
    if (!m_file) {
        return;
    }

    if (!readDosHeader() || !readNtHeader() || !readSectionHeaders()) {
        m_file.close();
        return;
    }

    m_isValid = true;
}

PEFile::~PEFile() {
    if (m_file.is_open()) {
        m_file.close();
    }
}

bool PEFile::readDosHeader() {
    m_file.read(reinterpret_cast<char*>(&m_dosHeader), sizeof(IMAGE_DOS_HEADER));
    if (!m_file || !validateDosHeader()) {
        return false;
    }
    return true;
}

bool PEFile::readNtHeader() {
    m_file.seekg(m_dosHeader.e_lfanew);
    m_file.read(reinterpret_cast<char*>(&m_ntHeader), sizeof(IMAGE_NT_HEADERS64));
    if (!m_file || !validateNtHeader()) {
        return false;
    }
    return true;
}

bool PEFile::readSectionHeaders() {
    m_sectionHeaders.resize(m_ntHeader.FileHeader.NumberOfSections);
    m_file.read(reinterpret_cast<char*>(m_sectionHeaders.data()), 
                sizeof(IMAGE_SECTION_HEADER) * m_ntHeader.FileHeader.NumberOfSections);
    return m_file.good();
}

bool PEFile::validateDosHeader() const {
    return m_dosHeader.e_magic == 0x5A4D;  // 'MZ'
}

bool PEFile::validateNtHeader() const {
    return m_ntHeader.Signature == 0x00004550;  // 'PE\0\0'
}

void PEFile::printHeaders() const {
    printDosHeader(m_dosHeader);
    printNtHeader(m_ntHeader);
    printOptionalHeader(m_ntHeader.OptionalHeader);
    printDataDirectories(m_ntHeader.OptionalHeader);
    printSectionTable(m_sectionHeaders.data(), m_ntHeader.FileHeader.NumberOfSections);
}





