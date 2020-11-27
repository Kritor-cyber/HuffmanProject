#include "Menu.h"

#include "Utilities.h"
#include "Encoding.h"
#include "FunctionsOfStructures/NodeAVLDictionnaryFunctions.h"
#include "FunctionsOfStructures/NodeHuffmanFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define DEBUG 1

void PrintMenu(const char* intro, int nbChoice, ...)
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	

    va_list args;
    va_start(args, nbChoice);

    printf("%s", intro);

    for (int i = 1; i <= nbChoice; i++)
    {
        printf("%d. %s\n", i, va_arg(args, char*));
    }

    va_end(args);
}

int GetUserChoice()
{
    printf("\nEnter your choice : ");
    int choice = -1;
	int result = scanf_s("%d", &choice);
	CleanInputBuffer();

    return choice;
}

char* GetStringFromUser(const char* msg)
{
	char* userString = (char*) malloc(sizeof(char)*32);
	
	if (userString == NULL)
	{
		printf("Error can't allocate memory for userString\n");
	}
	else
	{
		printf("%s", msg);
		if (scanf_s("%[^\n]", userString, 32) == 0) //%[^ \n] premet de récupérer tous les caractères sauf le retour à la ligne
		{
			printf("The text you entered is too long, you can't put more than 32 characters.\n");
		}

		CleanInputBuffer();
	}

	return userString;
}

void StartMenu()
{
	char stop = 0;
	int choice;
	while (!stop)
	{
		PrintMenu("What do you want to do ?\n", 3, "Compress a file", "Decompress a file", "Exit");

		choice = GetUserChoice();
		switch (choice)
		{
		case 1:
			printf("compression\n");
			CompressFile();
			break;
		case 2:
			printf("decompression\n");
			break;
		case 3:
			stop = 1;
			break;
		default:
			printf("Please enter a valid number\n");
			break;
		}

		Pause();
	}
}

static void CleanInputBuffer()
{
	while ((getchar()) != '\n');
}

static void Pause()
{
	printf("Press Enter to continue...");
	getchar(); // il y a un warning mais la valeur de retour ne nous intéresse pas
}

void CompressFile()
{
	char* pathOfFileToCompress = GetStringFromUser("Enter the path of the file you want to compress : ");
	if (pathOfFileToCompress != NULL)
	{
		if (pathOfFileToCompress[0] != '\0')
		{
			if (DEBUG) printf("Your entered : %s\n", pathOfFileToCompress);

			char* pathOfFileCompressed = AddStringBeforeExtensionOfFileName(pathOfFileToCompress, "_compressed");
			
			if (pathOfFileCompressed != NULL)
			{
				if (DEBUG) printf("The path of the compressed file : %s\n", pathOfFileCompressed);
				
				// Compression du fichier
				printf("Encoding %s\n", pathOfFileToCompress);

				NodeHuffman** tabTmp = NULL;
				int sizeTab;
				tabTmp = _CreateArrayOfNodeHuffmanWithNbOccFromFile(pathOfFileToCompress, &sizeTab);
				if (tabTmp != NULL)
				{
					NodeHuffman* huffTree = CreateHuffmanTreeFromArray(tabTmp, sizeTab);
					NodeAVLDictionnary* dictionnary = CreerAVLDictionnaire(huffTree);
					PrintNodeAVLDictionnary(dictionnary);
					EncodeFileAVLTree(pathOfFileToCompress, pathOfFileCompressed, dictionnary);
					printf("Encoding finished\n");

					FreeNodeAVLDictionnary(dictionnary);
					FreeHuffmanTree(huffTree);
					free(tabTmp);

					free(pathOfFileCompressed);
				}
			}
			else
			{
				printf("Failed to create the path of the compressed file\n");
			}
		}
		else
		{
			printf("The path you entered isn't valid\n");
		}
		free(pathOfFileToCompress);
	}
}