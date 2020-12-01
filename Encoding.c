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
	errno_t err = fopen_s(&fileToCompress, pathOfFileToCompress, "rb");
	if (err || fileToCompress == NULL)
	{
		printf("Can't open file %s for read\n", pathOfFileToCompress);
		PrintErrorMessageFromErrorCodeFromFile(err);
	}
	else
	{
		FILE* fileCompressed = NULL;
		err = fopen_s(&fileCompressed, pathOfFileCompressed, "wb");
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

void EncodeFileAVLTree(char* pathOfFileToCompress, BinaryFile* compressedFile, NodeAVLDictionnary* dic)
{
	FILE* fileToCompress = NULL;
	errno_t err = fopen_s(&fileToCompress, pathOfFileToCompress, "rb");
	if (err || fileToCompress == NULL)
	{
		printf("Can't open file %s for read\n", pathOfFileToCompress);
		PrintErrorMessageFromErrorCodeFromFile(err);
	}
	else
	{
		char c;
		char* code = NULL;
		while ((c = fgetc(fileToCompress)) != EOF)
		{
			code = GetCharCodeFromAVLDic(dic, c);
			WriteFakeBitsIntoBinaryFile(compressedFile, code);
		}

		fclose(fileToCompress);
	}
}

void WriteAVLDictionnary(NodeAVLDictionnary* tree, BinaryFile* fileWithDic)
{
	if (tree != NULL)
	{
		char codeSize = 0;
		while (tree->code[codeSize] != '\0')
			codeSize++;
		if (codeSize == 0) printf("CODE SIZE = 0\n");

		WriteCharIntoBinaryFile(fileWithDic, tree->c);
		WriteCharIntoBinaryFile(fileWithDic, codeSize);

		WriteFakeBitsIntoBinaryFile(fileWithDic, tree->code);

		WriteAVLDictionnary(tree->left, fileWithDic);
		WriteAVLDictionnary(tree->right, fileWithDic);
	}
}