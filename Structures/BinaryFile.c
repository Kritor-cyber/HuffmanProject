#include "BinaryFile.h"

#include <stdlib.h>

#include "../ASCIIToBinary.h"
#include "../Utilities.h"

BinaryFile* OpenBinaryFile(char* path, char* mode)
{
	BinaryFile* binaryFile = (BinaryFile*)malloc(sizeof(BinaryFile));

	if (binaryFile != NULL)
	{
		binaryFile->buffer = 0;
		binaryFile->sizeBuffer = 0;
		errno_t err = fopen_s(&(binaryFile->file), path, mode);
		if (err || binaryFile->file == NULL)
		{
			free(binaryFile);
			binaryFile = 0;
			printf("error opening file\n");
			PrintErrorMessageFromErrorCodeFromFile(err);
		}
	}

	return binaryFile;
}

void WriteCharIntoBinaryFile(BinaryFile* file, char charToWrite)
{
	char bitsCode[9];
	bitsCode[8] = '\0';
	CharacterToBinary(bitsCode, charToWrite);

	WriteFakeBitsIntoBinaryFile(file, bitsCode);
}

void WriteFakeBitsIntoBinaryFile(BinaryFile* file, char* bitsCode)
{
	int counter = 0;
	while (bitsCode[counter] != '\0')
	{
		WriteFakeBitIntoBinaryFile(file, bitsCode[counter]);
		counter++;
	}
}

void WriteFakeBitIntoBinaryFile(BinaryFile* file, char fakeBit)
{
	file->buffer = file->buffer << 1;
	file->sizeBuffer++;
	if (fakeBit == '1')
	{
		file->buffer += 1;
	}

	if (file->sizeBuffer == 8)
	{
		fprintf(file->file, "%c", (unsigned char) file->buffer);
		file->buffer = 0;
		file->sizeBuffer = 0;
	}
}

void ForceWriteBits(BinaryFile* file)
{
	while (file->buffer != 0)
	{
		WriteFakeBitIntoBinaryFile(file, '0');
	}
}

char GetCharFromBinaryFile(BinaryFile* file)
{
	char charGet = 0;

	for (int i = 0; i < 8; i++)
	{
		charGet = charGet << 1;
		charGet += GetFakeBitFromBinaryFile(file) == '1';
	}

	return charGet;
}

char GetFakeBitFromBinaryFile(BinaryFile* file)
{
	if (file->sizeBuffer == 0)
	{
		if (fscanf_s(file->file, "%c", &(file->buffer), 1) == EOF)
			return EOF;

		file->sizeBuffer = 8;
	}

	char bit = '0' + ((file->buffer & 0b10000000) != 0);
	file->buffer = file->buffer << 1;
	file->sizeBuffer--;

	return bit;
}

void CloseBinaryFile(BinaryFile* fileToClose)
{
	if (fileToClose != NULL)
	{
		fclose(fileToClose->file);
		free(fileToClose);
	}
}