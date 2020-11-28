#include "Utilities.h"

#include "Structures/ListCharAndNbOcc.h"
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
		fileNameExtension = fileName + strnlen_s(fileName, -1);
		if (fileNameExtension < fileName)
		{
			printf("error to find last char of file name without extension\n");
			exit(13);
		}
	}
	if (DEBUG) printf("%s\n", fileNameExtension);

	size_t resultSize = strnlen_s(fileName, -2) + strnlen_s(stringToAdd, -2) + 1;
	if (resultSize < strnlen_s(fileName, -1) || resultSize < strnlen_s(stringToAdd, -1))
	{
		printf("error to define result size\n");
		exit(13);
	}

	char* result = (char*)malloc(sizeof(char) * resultSize);
	if (result == NULL)
	{
		printf("error can't allocate memory to result\n");
		exit(13);
	}
	else
	{
		if (DEBUG) printf("%d nb cara avant extension\n", fileNameExtension - (fileName));
		errno_t err = strncpy_s(result, resultSize, fileName, (fileNameExtension - (fileName)));
		if (err != 0)
		{
			printf("error to copy file name\n");
			exit(13);
		}

		if (DEBUG) printf("nom fichier sans extension : %s\n", result);

		err = strcat_s(result, resultSize, stringToAdd);
		if (err != 0)
		{
			printf("error to concatenate file name\n");
			exit(13);
		}

		if (DEBUG) printf("nouveau nom fichier sans extension : %s\n", result);

		err = strcat_s(result, resultSize, fileNameExtension);

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