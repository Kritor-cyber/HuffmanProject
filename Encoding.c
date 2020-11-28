#include "Encoding.h"

#include <stdlib.h>
#include <string.h>
#include "Dictionnary.h"
#include "Utilities.h"

void GetCharCodeFromDic(FILE* dic, char c, char* code)
{
	if (fseek(dic, 0, SEEK_SET))
	{
		printf("Error while changing the file position indicator\n");
	}
	else
	{
		char charInDic;

		while ((charInDic = fgetc(dic)) != c && charInDic != EOF)
		{
			while ((charInDic = fgetc(dic)) != '\n');
		}

		if (charInDic != EOF)
		{
			if (fseek(dic, 3, SEEK_CUR))
			{
				printf("Error while changing the file position indicator to 3 on the right\n");
			}
			else
			{
				int cp = 0;
				while ((charInDic = fgetc(dic)) != '\n')
				{
					code[cp] = charInDic;
					cp++;
				}

				code[cp] = '\0';
			}
		}
	}
}

void EncodeFile(char* pathOfFileToCompress, char* pathOfFileCompressed, FILE* dic)
{
	FILE* fileToCompress = NULL;
	errno_t err = fopen_s(&fileToCompress, pathOfFileToCompress, "r");
	if (err || fileToCompress == NULL)
	{
		printf("Can't open file %s for read\n", pathOfFileToCompress);
		PrintErrorMessageFromErrorCodeFromFile(err);
	}
	else
	{
		FILE* fileCompressed = NULL;
		err = fopen_s(&fileCompressed, pathOfFileCompressed, "w");
		if (err || fileCompressed == NULL)
		{
			printf("Can't open file %s for read\n", pathOfFileCompressed);
			PrintErrorMessageFromErrorCodeFromFile(err);
		}
		else
		{
			char c;
			int maxCodeSize = GetMaxCodeSize();
			char* code = (char*)malloc(sizeof(char) * maxCodeSize);
			if (code == NULL)
			{
				printf("Error can't allocate memory to code\n");
			}
			else
			{
				while ((c = fgetc(fileToCompress)) != EOF)
				{
					GetCharCodeFromDic(dic, c, code);
					if (fprintf_s(fileCompressed, "%s", code) < 0)
					{
						printf("Error while writing into the compressed file\n");
					}
				}
				free(code);
			}

			fclose(fileCompressed);
		}
		fclose(fileToCompress);
	}
}

void EncodeFileAVLTree(char* pathOfFileToCompress, char* pathOfFileCompressed, NodeAVLDictionnary* dic)
{
	FILE* fileToCompress = NULL;
	errno_t err = fopen_s(&fileToCompress, pathOfFileToCompress, "r");
	if (err || fileToCompress == NULL)
	{
		printf("Can't open file %s for read\n", pathOfFileToCompress);
		PrintErrorMessageFromErrorCodeFromFile(err);
	}
	else
	{
		FILE* fileCompressed = NULL;
		err = fopen_s(&fileCompressed, pathOfFileCompressed, "w");
		if (err || fileCompressed == NULL)
		{
			printf("Can't open file %s for read\n", pathOfFileCompressed);
			PrintErrorMessageFromErrorCodeFromFile(err);
		}
		else
		{
			char c;
			char* code = NULL;
			while ((c = fgetc(fileToCompress)) != EOF)
			{
				code = GetCharCodeFromAVLDic(dic, c);
				if (fprintf_s(fileCompressed, "%s", code) < 0)
				{
					printf("Error while writing into the compressed file\n");
				}
			}

			fclose(fileCompressed);
		}
		fclose(fileToCompress);
	}
}

void WriteAVLDictionnary(NodeAVLDictionnary* tree, FILE* dic)
{
	if (tree != NULL)
	{
		fprintf_s(dic, "%c : %s\n", tree->c, tree->code);
		WriteAVLDictionnary(tree->left, dic);
		WriteAVLDictionnary(tree->right, dic);
	}
}