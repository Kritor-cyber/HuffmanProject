#include "Utilities.h"

#include "FunctionsOfStructures/ListCharAndNbOccFunctions.h"
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

void PrintErrorMessageFromErrorCodeFromFile(errno_t err)
{
	char* buffer = (char*)malloc(sizeof(char) * 1024);
	if (buffer != NULL)
	{
		strerror_s(buffer, 1024, err);
		printf("\n\n%s\n\n", buffer);
		free(buffer);
	}
	else
	{
		printf("can't allocate memory to buffer (error for opening file : %d)\n", err);
	}
}

char* AddStringBeforeExtensionOfFileName(char* fileName, char* stringToAdd)
{
	char* fileNameExtension = strrchr(fileName, '.');
	if (fileNameExtension == NULL)
	{
		fileNameExtension = fileName + strnlen_s(fileName, 0);
		if (fileNameExtension < fileName)
		{
			printf("error to find last char of file name without extension\n");
			return NULL;
		}
	}
	if (DEBUG) printf("%s\n", fileNameExtension);

	size_t resultSize = strnlen_s(fileName, 32) + strnlen_s(stringToAdd, 32) + 1;
	if (resultSize < strnlen_s(fileName, 32) || resultSize < strnlen_s(stringToAdd, 32))
	{
		printf("error to define result size\n");
		return NULL;
	}

	char* result = (char*)malloc(sizeof(char) * resultSize);
	if (result == NULL)
	{
		printf("error can't allocate memory to result\n");
		return NULL;
	}
	else
	{
		if (DEBUG) printf("%d nb cara avant extension\n", (int) (fileNameExtension - (fileName)));
		errno_t err = strncpy_s(result, resultSize, fileName, (fileNameExtension - (fileName)));
		if (err != 0)
		{
			printf("error to copy file name\n");
			free(result);
			return NULL;
		}

		if (DEBUG) printf("nom fichier sans extension : %s\n", result);

		err = strcat_s(result, resultSize, stringToAdd);
		if (err != 0)
		{
			printf("error to concatenate file name\n");
			free(result);
			return NULL;
		}

		if (DEBUG) printf("nouveau nom fichier sans extension : %s\n", result);

		err = strcat_s(result, resultSize, fileNameExtension);

		if (err)
		{
			printf("An error occured while adding string before extension of file name (error : %d)\n", err);
		}

		if (DEBUG) printf("nouveau nom fichier : %s\n", result);

		return result;
	}

	return NULL;
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

void WriteInBinary(FILE* file, char* string)
{
	int cp = 0;
	char binary = 0;

	while (string[cp] != '\0')
	{
		binary = binary << 1;
		if (string[cp] == '1')
		{
			binary = binary | 0b00000001;
		}
		else if (string[cp] != '0')
		{
			printf("To convert fake binary to real binary, the string needs to be only composed by '0' and '1' (no %c)\n", string[cp]);
		}

		if (cp % 8 == 0 && cp != 0)
		{
			fprintf(file, "%c", binary);
			binary = 0;
		}

		cp++;
	}

	if ((cp-1) % 8 != 0)
	{
		fprintf(file, "%c", binary);
	}
}