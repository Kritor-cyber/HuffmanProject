#include "FileManipulation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StringManipulation.h"
#include "Utilities.h"

#define DEBUG 0

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

int GetNumberCharInFile(char* path)
{
	int nbCharInFile = -1;
	FILE* fileToRead;
	errno_t err = fopen_s(&fileToRead, path, "r");

	if (DEBUG) printf("chemin vers le fichier a ouvrir : %s\n", path);

	if (err || fileToRead == NULL)
	{
		printf("Can't open file \"%s\"\n", path);

		PrintErrorMessageFromErrorCodeFromFile(err);

		return nbCharInFile;
	}
	else
	{
		char c;
		ListCharAndNbOcc* list = NULL;
		while ((c = getc(fileToRead)) != EOF)
		{
			AddCharToList(&list, c);
		}

		if (list != NULL)
		{
			nbCharInFile = GetNbOccSum(list);

			FreeList(list);
		}
		
		fclose(fileToRead);
	}

	return nbCharInFile;
}

ListCharAndNbOcc* GetListCharAndNbOccFromFile(char* path)
{
	FILE* fileToRead;
	errno_t err = fopen_s(&fileToRead, path, "r");

	if (DEBUG) printf("chemin vers le fichier a ouvrir : %s\n", path);

	if (err || fileToRead == NULL)
	{
		printf("Can't open file \"%s\"\n", path);

		PrintErrorMessageFromErrorCodeFromFile(err);

		return NULL;
	}
	else
	{
		char c;
		ListCharAndNbOcc* list = NULL;
		while ((c = getc(fileToRead)) != EOF)
		{
			AddCharToList(&list, c);
		}

		fclose(fileToRead);

		if (list != NULL)
		{
			return list;
		}
	}

	return NULL;
}