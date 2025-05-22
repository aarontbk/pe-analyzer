#pragma once
#include <cstdio>

class FileReader {
public:
    static bool readHeader(FILE* file, void* header, size_t size, long offset = 0);
}; 