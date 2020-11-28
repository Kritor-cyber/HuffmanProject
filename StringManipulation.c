#include "StringManipulation.h"

#include <stdio.h>
/*#include <stdlib.h>*/
#include <string.h>

#define DEBUG_MODE 0

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
	if (DEBUG_MODE) printf("%s\n", fileNameExtension);

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
		if (DEBUG_MODE) printf("%d nb cara avant extension\n", fileNameExtension - (fileName));
		errno_t err = strncpy_s(result, resultSize, fileName, (fileNameExtension - (fileName)));
		if (err != 0)
		{
			printf("error to copy file name\n");
			exit(13);
		}

		if (DEBUG_MODE) printf("nom fichier sans extension : %s\n", result);

		err = strcat_s(result, resultSize, stringToAdd);
		if (err != 0)
		{
			printf("error to concatenate file name\n");
			exit(13);
		}

		if (DEBUG_MODE) printf("nouveau nom fichier sans extension : %s\n", result);

		err = strcat_s(result, resultSize, fileNameExtension);

		if (DEBUG_MODE) printf("nouveau nom fichier : %s\n", result);

		return result;
	}

	return NULL;
}

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