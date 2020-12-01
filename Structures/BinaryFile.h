#pragma once

#include <stdio.h>

typedef struct BinaryFile
{
	FILE* file;
	char buffer;
	char sizeBuffer;
} BinaryFile;

BinaryFile* OpenBinaryFile(char* path, char* mode);

void WriteCharIntoBinaryFile(BinaryFile* file, char charToWrite);

void WriteFakeBitsIntoBinaryFile(BinaryFile* file, char* bitsCode);

void WriteFakeBitIntoBinaryFile(BinaryFile* file, char fakeBit);

void ForceWriteBits(BinaryFile* file);

char GetCharFromBinaryFile(BinaryFile* file);

char GetFakeBitFromBinaryFile(BinaryFile* file);

void CloseBinaryFile(BinaryFile* fileToClose);