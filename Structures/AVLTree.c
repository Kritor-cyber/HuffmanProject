#include "AVLTree.h"

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

NodeAVLDictionnary* CreerAVLDictionnaire(NodeHuffman* tree)
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
		_CreerAVLDictionnaire(tree, code, 1, &nodeAVLDictionnary);
		AVLBalance(&nodeAVLDictionnary);
	}

	return nodeAVLDictionnary;
}


void _CreerAVLDictionnaire(NodeHuffman* actualNode, char* code, int codeSize, NodeAVLDictionnary** tree)
{
	if (actualNode == NULL)
	{
		printf("The node must be not NULL\n");
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
			if (newCode == NULL)
			{
				printf("failed to allocte memory to newCode (%d bytes).\n", codeSize);
			}
			else
			{
				errno_t err = strcpy_s(newCode, codeSize, code);
				if (err)
				{
					printf("failed to copy the code %s (error code : %d)\n", code, err);
				}
				else
				{
					newCode[codeSize - 2] = -1;
					newCode[codeSize - 1] = '\0';

					if (actualNode->left != NULL)
					{
						newCode[codeSize - 2] = '0';
						_CreerAVLDictionnaire(actualNode->left, newCode, codeSize, tree);
					}
					if (actualNode->right != NULL)
					{
						if (newCode[codeSize - 2] == -1)
						{
							newCode[codeSize - 2] = '1';
							_CreerAVLDictionnaire(actualNode->right, newCode, codeSize, tree);
						}
						else
						{
							char* newCode2 = (char*)malloc(sizeof(char) * codeSize);
							if (newCode2 == NULL)
							{
								printf("failed to allocte memory to newCode2 (%d bytes).\n", codeSize);
							}
							else
							{
								errno_t err = strcpy_s(newCode2, codeSize, code);
								if (err)
								{
									printf("failed to copy the code %s (error code : %d)\n", code, err);
								}
								else
								{
									newCode2[codeSize - 2] = '1';
									newCode2[codeSize - 1] = '\0';
									_CreerAVLDictionnaire(actualNode->right, newCode2, codeSize, tree);
								}
							}
						}
					}
				}
			}
		}

	}
}

int _AVLDepth(NodeAVLDictionnary* tree)
{
	if (tree == NULL) return -1;
	int h1 = _AVLDepth(tree->left), h2 = _AVLDepth(tree->right);

	if (h1 > h2)
		return h1 + 1;

	return h2 + 1;
}

int _AVLBalanceFactor(NodeAVLDictionnary* tree)
{
	if (tree == NULL)
		return 0;

	return _AVLDepth(tree->right) - _AVLDepth(tree->left);
}

void _AVLRightRotation(NodeAVLDictionnary** tree)
{
	if (*tree != NULL)
	{
		NodeAVLDictionnary* temp = (*tree)->left;

		(*tree)->left = temp->right;
		temp->right = *tree;
		*tree = temp;
	}
}

void _AVLLeftRotation(NodeAVLDictionnary** tree)
{
	if (*tree != NULL)
	{
		NodeAVLDictionnary* temp = (*tree)->right;

		(*tree)->right = temp->left;
		temp->left = (*tree);
		*tree = temp;
	}
}

void AVLBalance(NodeAVLDictionnary** tree)
{
	if (*tree != NULL)
	{
		AVLBalance(&((*tree)->left));
		AVLBalance(&((*tree)->right));

		int bf = _AVLBalanceFactor(*tree);

		if (bf <= -2)
		{
			if (_AVLBalanceFactor((*tree)->left) > 0)
			{
				_AVLLeftRotation(&((*tree)->left));
			}

			_AVLRightRotation(tree);
		}
		else if (bf >= 2)
		{
			if (_AVLBalanceFactor((*tree)->right) < 0)
			{
				_AVLRightRotation(&((*tree)->right));
			}

			_AVLLeftRotation(tree);
		}
	}
}


void PrintNodeAVLDictionnary(NodeAVLDictionnary* tree)
{
	if (tree != NULL)
	{
		printf("%c : %s\n", tree->c, tree->code);
		printf("left child\n");
		PrintNodeAVLDictionnary(tree->left);
		printf("right child\n");
		PrintNodeAVLDictionnary(tree->right);
	}
	
	printf("go up\n");
}

void FreeNodeAVLDictionnary(NodeAVLDictionnary* tree)
{
	if (tree != NULL)
	{
		FreeNodeAVLDictionnary(tree->left);
		FreeNodeAVLDictionnary(tree->right);
		free(tree->code);
		free(tree);
	}
}