#include "Decoding.h"

#include <stdio.h>
#include "Utilities.h"

void DecodeFromTree(const char* pathToTheFileToDecode, const char* pathToTheDecodedFile, NodeHuffman* tree)
{
	FILE* fileToDecode = NULL;
	errno_t err = fopen_s(&fileToDecode, pathToTheFileToDecode, "r");
	
	if (err || fileToDecode == NULL)
	{
		printf("Error while opening \"%s\" to decode\n", pathToTheFileToDecode);
		PrintErrorMessageFromErrorCodeFromFile(err);
	}
	else
	{
		FILE* fileDecoded = NULL;
		err = fopen_s(&fileDecoded, pathToTheDecodedFile, "w");

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

				if (tmpHuffmanTree->c != NULL)
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