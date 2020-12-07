#include "NodeAVLDictionnary.h"
#include "../FunctionsOfStructures/NodeAVLDictionnaryFunctions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AddNodeInNodeDictionnary(NodeAVLDictionnary** dic, char c, char* code)
{
	if ((*dic) == NULL)
	{
		(*dic) = (NodeAVLDictionnary*)malloc(sizeof(NodeAVLDictionnary));
		if ((*dic) == NULL)
		{
			printf("Can't allocate memory for a node of NodeAVLDictionnary\n");
		}
		else
		{
			(*dic)->c = c;
			(*dic)->code = code;
			(*dic)->left = NULL;
			(*dic)->right = NULL;
		}
	}
	else
	{
		if ((*dic)->c > c)
		{
			AddNodeInNodeDictionnary(&((*dic)->left), c, code);
		}
		else
		{
			AddNodeInNodeDictionnary(&((*dic)->right), c, code);
		}
	}
}

NodeAVLDictionnary* CreateAVLDictionnary(NodeHuffman* tree)
{
	if (tree == NULL)
	{
		printf("The Huffman tree must not be NULL\n");
		return NULL;
	}
	
	NodeAVLDictionnary* nodeAVLDictionnary = NULL;
	if (tree->left == NULL && tree->right == NULL)
	{
		char* code = (char*)malloc(sizeof(char) * 2);
		if (code == NULL)
		{
			printf("can't allocate memory to code (2 bytes).\n");
		}
		else
		{
			code[0] = '0';
			code[1] = '\0';
			AddNodeInNodeDictionnary(&nodeAVLDictionnary, tree->c, code);
		}
		return nodeAVLDictionnary;
	}
	
	char* code = (char*)malloc(sizeof(char));
	if (code == NULL)
	{
		printf("Can't allocate memory to one char\n");
		return NULL;
	}
	else
	{
		code[0] = '\0';
		_CreateAVLDictionnary(tree, code, 1, &nodeAVLDictionnary);
		AVLBalance(&nodeAVLDictionnary);
	}

	return nodeAVLDictionnary;
}

void _CreateAVLDictionnary(NodeHuffman* actualNode, char* code, int codeSize, NodeAVLDictionnary** tree)
{
	if (actualNode == NULL)
	{
		printf("The node must not be NULL\n");
	}
	else
	{
		if (actualNode->left == NULL && actualNode->right == NULL)
		{
			AddNodeInNodeDictionnary(tree, actualNode->c, code);
			AVLBalance(tree);
		}
		else
		{
			codeSize++;
			char* newCode = (char*)malloc(sizeof(char) * codeSize);
			char* newCode2 = (char*)malloc(sizeof(char) * codeSize);
			if (newCode == NULL || newCode2 == NULL)
			{
				printf("failed to allocte memory to newCode (%d bytes) and/or to newCode2.\n", codeSize);
			}
			else
			{
				errno_t err = strcpy_s(newCode, codeSize, code);
				free(code);

				if (err)
				{
					printf("failed to copy the code %s (error code : %d)\n", code, err);
				}
				else
				{

					err = strcpy_s(newCode2, codeSize, newCode);
					if (err)
					{
						printf("failed to copy the newCode %s to newCode2 (error code : %d)\n", newCode, err);
					}
					else
					{
						newCode[codeSize - 1] = '\0';
						newCode2[codeSize - 1] = '\0';

						if (actualNode->left != NULL)
						{
							newCode[codeSize - 2] = '0';
							_CreateAVLDictionnary(actualNode->left, newCode, codeSize, tree);
						}
						else
							printf("This should never happened (in _CreerAVLDictionnaire in NodeAVLDictionnary.c, the first)\n");

						if (actualNode->right != NULL)
						{
							newCode2[codeSize - 2] = '1';
							_CreateAVLDictionnary(actualNode->right, newCode2, codeSize, tree);
						}
						else
							printf("This should never happened (in _CreerAVLDictionnaire in NodeAVLDictionnary.c, the second)\n");
					}
				}
			}
		}

	}
}

char* GetCharCodeFromAVLDic(NodeAVLDictionnary* dic, char c)
{
	while (dic != NULL)
	{
		if (c > dic->c)
		{
			dic = dic->right;
		}
		else if (c < dic->c)
		{
			dic = dic->left;
		}
		else if (c == dic->c)
		{
			return dic->code;
		}
	}

	return NULL;
}