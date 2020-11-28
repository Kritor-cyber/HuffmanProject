#include "Menu.h"

#include "ASCIIToBinary.h"
#include "Utilities.h"
#include "Encoding.h"
#include "Decoding.h"
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
		PrintMenu("What do you want to do ?\n", 4, "Compress a file", "Decompress a file", "Convert a file into fake binary", "Exit");

		choice = GetUserChoice();
		switch (choice)
		{
		case 1:
			printf("compression\n");
			CompressFile();
			break;
		case 2:
			printf("decompression\n");
			DecompressFile();
			break;
		case 3:
			ConvertIntoFakeBinary();
			break;
		case 4:
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

				// Those two next lines produces the same result but the first one use dichotomy
				//tabTmp = CreateArrayOfNodeHuffmanWithNbOccFromFile(pathOfFileToCompress, &sizeTab);
				tabTmp = _CreateArrayOfNodeHuffmanWithNbOccFromFile(pathOfFileToCompress, &sizeTab);
				if (tabTmp != NULL)
				{
					NodeHuffman* huffTree = CreateHuffmanTreeFromArray(tabTmp, sizeTab);
					NodeAVLDictionnary* dictionnary = CreerAVLDictionnaire(huffTree);
					EncodeFileAVLTree(pathOfFileToCompress, pathOfFileCompressed, dictionnary);
					
					FILE* dictionnaryFile = NULL;
					errno_t err = fopen_s(&dictionnaryFile, "dico.txt", "w");
					
					if (err || dictionnaryFile == NULL)
					{
						printf("Encoding finished but can't open the file \"dico.txt\" into write mode\n");

						PrintErrorMessageFromErrorCodeFromFile(err);
					}
					else
					{
						WriteAVLDictionnary(dictionnary, dictionnaryFile);
						printf("Encoding finished and dictionnary write\n");
						fclose(dictionnaryFile);
					}

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

void DecompressFile()
{
	char* pathOfCompressedFile = GetStringFromUser("Enter the path of the file you want to decompress : ");
	if (pathOfCompressedFile != NULL && pathOfCompressedFile[0] != '\0')
	{
		char* pathOfDecompressedFile = GetStringFromUser("Enter the path of the decompressed file : ");

		if (pathOfDecompressedFile != NULL && pathOfDecompressedFile[0] != '\0')
		{
			NodeHuffman* treeToDecompress = CreateHuffmanTreeFromDictionnaryFile("dico.txt");
			if (treeToDecompress != NULL)
			{
				printf("Decoding %s\n", pathOfCompressedFile);
				DecodeFromTree(pathOfCompressedFile, pathOfDecompressedFile, treeToDecompress);
				FreeHuffmanTree(treeToDecompress);
				printf("Decoding finished\n");
			}

			free(pathOfDecompressedFile);
		}

		free(pathOfCompressedFile);
	}
}

void ConvertIntoFakeBinary()
{
	char* path = GetStringFromUser("Enter the path to the file you want to convert into fake binary : ");
	ConvertFileFromASCIIToBinary(path);
	free(path);
}