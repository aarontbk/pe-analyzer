#pragma once
#include "PEStructs.h"
#include <iostream>

void printDosHeader(const IMAGE_DOS_HEADER& header);
void printNtHeader(const IMAGE_NT_HEADERS32& header); 