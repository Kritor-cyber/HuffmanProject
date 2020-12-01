#include "Encoding.h"

#include <stdlib.h>
#include <string.h>
#include "Utilities.h"

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