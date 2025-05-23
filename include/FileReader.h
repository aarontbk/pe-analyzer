#pragma once
#include <cstdio>
#include <string>

class FileReader {
public:
    static FILE* openFile(const char* filePath, std::string& errorMessage);
    static void closeFile(FILE* file);
    static bool readHeader(FILE* file, void* header, size_t size, long offset = 0);
}; 