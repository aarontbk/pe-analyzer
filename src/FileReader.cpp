#include "FileReader.h"

bool FileReader::readHeader(FILE* file, void* header, size_t size, long offset) {
    if (offset != 0) {
        if (fseek(file, offset, SEEK_SET) != 0) {
            return false;
        }
    }
    return fread(header, size, 1, file) == 1;
} 