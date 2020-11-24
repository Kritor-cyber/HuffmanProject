#include "ASCIIToBinary.h"

#include "Utilities.h"
#include <stdlib.h>

#define DEBUG 0

void CharacterToBinary(char* bitsComposingChar, char charToConvert)
{
	if (bitsComposingChar == NULL)
	{
		printf("error no memory allocated to contain the binary version of char\n");
	}
	else
	{
		for (int i = 7; i >= 0; i--)
		{
			bitsComposingChar[i] = '0' + (int)(charToConvert & 0b00000001);
			charToConvert = charToConvert >> 1;
		}
	}
}

void ConvertFileFromASCIIToBinary(char* path)
{
	FILE* fileToRead;
	errno_t err = fopen_s(&fileToRead, path, "r");

	if (DEBUG) printf("chemin vers le fichier a ouvrir : %s\n", path);

	if (err || fileToRead == NULL)
	{
		printf("Can't open file \"%s\"\n", path);

		PrintErrorMessageFromErrorCodeFromFile(err);
	}
	else
	{
		char* pathToBinary = AddStringBeforeExtensionOfFileName(path, "_binary");
		if (DEBUG) printf("chemin vers le fichier a ecrire : %s\n", pathToBinary);
		FILE* fileToWrite;
		err = fopen_s(&fileToWrite, pathToBinary, "w");

		if (err || fileToWrite == NULL)
		{
			printf("Can't open file \"%s\"\n", pathToBinary);

			PrintErrorMessageFromErrorCodeFromFile(err);
		}
		else
		{
			char binaryResult[8];
			char c;
			while ((c = getc(fileToRead)) != EOF)
			{
				CharacterToBinary(binaryResult, c);
				if (DEBUG) printf("%c : %.*s\n", c, 8, binaryResult);
				fwrite(binaryResult, sizeof(char), 8, fileToWrite);
			}

			fclose(fileToWrite);
		}

		free(pathToBinary);
		fclose(fileToRead);
	}
}