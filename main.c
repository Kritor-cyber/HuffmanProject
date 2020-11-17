#include <stdio.h>
#include <stdlib.h>

#include "StringManipulation.h"
#include "FileManipulation.h"
#include "Structures/ListCharAndNbOcc.h"
#include "Structures/NodeHuffman.h"
#include "Encoding.h"
#include "Decoding.h"
#include "Dictionnary.h"

#define DEBUG 1

int main(int argc, char* argv[])
{
	printf("Compression de fichiers textes...\n\n");
	if (argc != 2 && argc != 3)
	{
		printf("usage Huffman.exe \"file to compress.txt\"\nor\n");
		printf("usage Huffman.exe \"file to compress.txt\" \"name of the compressed file.txt\"\n");
		return 0;
	}


	printf("Gonna convert \"%s\" into binary...\n", argv[1]);

	ConvertFileFromASCIIToBinary(argv[1]);
	printf("\"%s\" into binary convertion finished...\n", argv[1]);

	char* binaryFile = AddStringBeforeExtensionOfFileName(argv[1], "_binary");
	int nbCharInFile = GetNumberCharInFile(argv[1]);
	if (nbCharInFile == -1)
		printf("There is no character in %s\n", argv[1]);
	else
		printf("There are %d char in %s\n", nbCharInFile, argv[1]);

	nbCharInFile = GetNumberCharInFile(binaryFile);
	if (nbCharInFile == -1)
		printf("There is no character in %s\n", binaryFile);
	else
		printf("There are %d char in %s\n", GetNumberCharInFile(binaryFile), binaryFile);
	
	free(binaryFile);

	ListCharAndNbOcc* list = GetListCharAndNbOccFromFile(argv[1]);

	if (list == NULL)
	{
		printf("file is empty or an eeror occurred\n");
	}
	else
	{
		if (DEBUG)
		{
			PrintList(list);
			NodeHuffman* huffmanTree = CreateHuffmanTree(list);
			PrintList(list);
			PrintHuffmanTree(huffmanTree);
			WriteDictionnary(huffmanTree);

			
			FILE* dic = NULL;
			errno_t err = fopen_s(&dic, "dico.txt", "r");

			if (err || dic == NULL)
			{
				printf("There is an error while opening the dictionnary\n");
			}
			else
			{
				char* pathOfFileCompressed = AddStringBeforeExtensionOfFileName(argv[1], "_compressed");
				if (pathOfFileCompressed == NULL)
				{
					printf("Error while allocating memory to pathOfFileCompressed\n");
				}
				else
				{
					printf("Encoding %s\n", argv[1]);
					EncodeFile(argv[1], pathOfFileCompressed, dic);
					printf("Encoding finished\n", argv[1]);

					char* pathOfFileDecompressed = AddStringBeforeExtensionOfFileName(argv[1], "_decompressed");
					if (pathOfFileDecompressed == NULL)
					{
						printf("Error while allocating memory to pathOfFileCompressed\n");
					}
					else
					{
						printf("Decoding %s\n", pathOfFileCompressed);
						DecodeFromTree(pathOfFileCompressed, pathOfFileDecompressed, huffmanTree);
						printf("Decoding finished\n", pathOfFileCompressed);
						free(pathOfFileDecompressed);
					}

					free(pathOfFileCompressed);
				}
			}

			FreeList(list);
			list = NULL;
			FreeHuffmanTree(huffmanTree);
			huffmanTree = NULL;
		}
	}

	return 0;
}