#include "FileReader.h"
#include <iostream>

FILE* FileReader::openFile(const char* filePath, std::string& errorMessage) {
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        errorMessage = "Error opening file: " + std::string(filePath);
        perror("fopen");
    }
    return file;
}

void FileReader::closeFile(FILE* file) {
    if (file) {
        fclose(file);
    }
}

bool FileReader::readHeader(FILE* file, void* header, size_t size, long offset) {
    if (offset != 0) {
        if (fseek(file, offset, SEEK_SET) != 0) {
            return false;
        }
    }
    return fread(header, size, 1, file) == 1;
} 