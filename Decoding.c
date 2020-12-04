#include "Decoding.h"

#include <stdio.h>
#include "Utilities.h"
#include "FunctionsOfStructures/NodeHuffmanFunctions.h"
#include "Structures/BinaryFile.h"

void DecodeFromTree(const char* pathToTheFileToDecode, const char* pathToTheDecodedFile, NodeHuffman* tree)
{
	FILE* fileToDecode = NULL;
	errno_t err = fopen_s(&fileToDecode, pathToTheFileToDecode, "rb");
	
	if (err || fileToDecode == NULL)
	{
		printf("Error while opening \"%s\" to decode\n", pathToTheFileToDecode);
		PrintErrorMessageFromErrorCodeFromFile(err);
	}
	else
	{
		FILE* fileDecoded = NULL;
		err = fopen_s(&fileDecoded, pathToTheDecodedFile, "wb");

		if (err || fileDecoded == NULL)
		{
			printf("Error while opening \"%s\" to write decoded text\n", pathToTheDecodedFile);
			PrintErrorMessageFromErrorCodeFromFile(err);
		}
		else
		{
			char c;
			NodeHuffman* tmpHuffmanTree = tree;

			while ((c = fgetc(fileToDecode)) != EOF)
			{
				if (c == '0')
				{
					tmpHuffmanTree = tmpHuffmanTree->left;
				}
				else if (c == '1')
				{
					tmpHuffmanTree = tmpHuffmanTree->right;
				}

				if (tmpHuffmanTree->c != '\0')
				{
					if (fprintf_s(fileDecoded, "%c", tmpHuffmanTree->c) < 0)
					{
						printf("error while writing into fileDecoded\n");
					}
					else
					{
						tmpHuffmanTree = tree;
					}
				}
			}

			fclose(fileDecoded);
		}
		fclose(fileToDecode);
	}
}

void DecodeCompressedFileWithIntegratedTree(char* pathToTheFileToDecode, char* pathToTheDecodedFile)
{
	BinaryFile* binaryFileToDecode = OpenBinaryFile(pathToTheFileToDecode, "rb");

	if (binaryFileToDecode == NULL)
	{
		printf("Error while opening \"%s\" to decode\n", pathToTheFileToDecode);
	}
	else
	{
		FILE* fileDecoded = NULL;
		errno_t err = fopen_s(&fileDecoded, pathToTheDecodedFile, "wb");

		if (err || fileDecoded == NULL)
		{
			printf("Error while opening \"%s\" to write decoded text\n", pathToTheDecodedFile);
			PrintErrorMessageFromErrorCodeFromFile(err);
		}
		else
		{
			NodeHuffman* tree = CreateHuffmanTreeFromDictionnaryIntegratedInFile(binaryFileToDecode);

			if (tree != NULL)
			{
				char c;
				NodeHuffman* tmpHuffmanTree = tree;

				char end = 0;
				while (!end && (c = GetFakeBitFromBinaryFile(binaryFileToDecode)) != EOF)
				{
					if (c == '0')
					{
						tmpHuffmanTree = tmpHuffmanTree->left;
					}
					else if (c == '1')
					{
						tmpHuffmanTree = tmpHuffmanTree->right;
					}

					if (tmpHuffmanTree->c != '\0')
					{
						if (fprintf_s(fileDecoded, "%c", tmpHuffmanTree->c) < 0)
						{
							printf("error while writing into fileDecoded\n");
						}
						else
						{
							tmpHuffmanTree = tree;
						}
					}
					else if (tmpHuffmanTree->nbOcc != 0)
					{
						end = 1;
					}
				}

				FreeHuffmanTree(tree);
			}

			fclose(fileDecoded);
		}
		CloseBinaryFile(binaryFileToDecode);
	}
}