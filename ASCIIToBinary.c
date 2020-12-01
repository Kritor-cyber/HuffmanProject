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
		FILE* fileToWrite = NULL;
		err = fopen_s(&fileToWrite, pathToBinary, "w");

		if (err || fileToWrite == NULL)
		{
			printf("Can't open file \"%s\"\n", pathToBinary);

			PrintErrorMessageFromErrorCodeFromFile(err);
		}
		else
		{

			char* pathToRealBinary = AddStringBeforeExtensionOfFileName(path, "_real_binary");
			if (pathToRealBinary != NULL)
			{
				FILE* realBinaryFileToWrite = NULL;
				err = fopen_s(&realBinaryFileToWrite, pathToRealBinary, "w");

				if (err || realBinaryFileToWrite == NULL)
				{
					printf("Can't open file \"%s\"\n", pathToRealBinary);

					PrintErrorMessageFromErrorCodeFromFile(err);
				}
				else
				{

					char binaryResult[9];
					binaryResult[8] = '\0';
					char c;
					while ((c = getc(fileToRead)) != EOF)
					{
						CharacterToBinary(binaryResult, c);
						if (DEBUG) printf("%c : %.*s\n", c, 8, binaryResult);
						fwrite(binaryResult, sizeof(char), 8, fileToWrite);

						WriteInBinary(realBinaryFileToWrite, binaryResult);
					}

					fclose(realBinaryFileToWrite);
					free(pathToRealBinary);
				}
			}
			fclose(fileToWrite);
		}

		free(pathToBinary);
		fclose(fileToRead);
	}
}