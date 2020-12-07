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

#include "Structures/BinaryFile.h"

#define DEBUG 1

void CleanScreen()
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void PrintMenu(const char* intro, int nbChoice, ...)
{
	CleanScreen();
	

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

	if (scanf_s("%d", &choice) == 0)
	{
		printf("An error occured while reading your choice\n");
	}

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
	while (!stop)
	{
		PrintMenu("What do you want to do ?\n", 4, "Compress a file", "Decompress a file", "Convert a file into fake binary", "Exit");

		int choice = GetUserChoice();
		switch (choice)
		{
		case 1:
			CleanScreen();
			printf("Compression\n\n\n");
			CompressFile();
			break;
		case 2:
			CleanScreen();
			printf("Decompression\n\n\n");
			DecompressFile();
			break;
		case 3:
			CleanScreen();
			ConvertIntoFakeBinary();
			break;
		case 4:
			stop = 1;
			break;
		default:
			printf("Please enter a valid number\n");
			break;
		}

		if (choice != 4)
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
					SortArrayByNbOcc(tabTmp, sizeTab);
					NodeHuffman* huffTree = CreateHuffmanTreeFromArray(tabTmp, sizeTab);
					NodeAVLDictionnary* dictionnary = CreateAVLDictionnary(huffTree);

					BinaryFile* compressedFileWithDictionnary = OpenBinaryFile(pathOfFileCompressed, "wb");

					if (compressedFileWithDictionnary == NULL)
					{
						printf("Can't open the binary file \"%s\" into write mode to write dictionnary\n", pathOfFileCompressed);
					}
					else
					{
						WriteAVLDictionnary(dictionnary, compressedFileWithDictionnary);
						WriteCharIntoBinaryFile(compressedFileWithDictionnary, dictionnary->c);

						EncodeFileAVLTree(pathOfFileToCompress, compressedFileWithDictionnary, dictionnary);

						char* code = NULL;
						code = GetCharCodeFromAVLDic(dictionnary, '\0');
						WriteFakeBitsIntoBinaryFile(compressedFileWithDictionnary, code);
						ForceWriteBits(compressedFileWithDictionnary);

						printf("Encoding finished and dictionnary write\n");
					}
					
					CloseBinaryFile(compressedFileWithDictionnary);
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
			printf("Decoding %s\n", pathOfCompressedFile);
			DecodeCompressedFileWithIntegratedTree(pathOfCompressedFile, pathOfDecompressedFile);
			printf("Decoding finished\n");

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