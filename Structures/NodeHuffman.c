#include "NodeHuffman.h"

#include "ListHuffman.h"
#include "../Utilities.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NodeHuffman* CreateHuffmanTree(ListCharAndNbOcc *list)
{
	NodeHuffman* nextNode = NULL;
	ListHuffman* listTree = NULL;
	NodeHuffman* leftChild = NULL;
	NodeHuffman* rightChild = NULL;

	SortListCharAndNbOccCroissant(&list);

	while (list != NULL || listTree != NULL)
	{
		if (listTree == NULL)
		{
			leftChild = NodeHuffmanFromNodeCharAndNbOcc(list);
			if (list != NULL)
				list = list->next;
		}
		else if (list != NULL && listTree->data->nbOcc < list->nbOcc)
		{
			leftChild = listTree->data;
			listTree = listTree->next;
		}
		else
		{
			if (list == NULL)
			{
				leftChild = listTree->data;
				listTree = listTree->next;
			}
			else
			{
				leftChild = NodeHuffmanFromNodeCharAndNbOcc(list);
				list = list->next;
			}
		}

		if (listTree == NULL)
		{
			rightChild = NodeHuffmanFromNodeCharAndNbOcc(list);
			if (list != NULL)
				list = list->next;
		}
		else if (list != NULL && listTree->data->nbOcc < list->nbOcc)
		{
			rightChild = listTree->data;
			listTree = listTree->next;
		}
		else
		{
			if (list == NULL)
			{
				rightChild = listTree->data;
				listTree = listTree->next;
			}
			else
			{
				rightChild = NodeHuffmanFromNodeCharAndNbOcc(list);
				list = list->next;
			}
		}

		if (rightChild != NULL)
		{
			nextNode = (NodeHuffman*)malloc(sizeof(NodeHuffman));
			if (nextNode != NULL)
			{
				nextNode->c = NULL;
				nextNode->nbOcc = leftChild->nbOcc + rightChild->nbOcc;
				nextNode->left = leftChild;
				nextNode->right = rightChild;
				AddToListHuffman(&listTree, nextNode);
			}
			else
			{
				printf("WARNING : Impossible to allocate memory to a node of the tree. The program failed.\n\n");
			}
		}
	}

	return nextNode;
}

NodeHuffman* NodeHuffmanFromNodeCharAndNbOcc(ListCharAndNbOcc* list)
{
	if (list == NULL)
		return NULL;

	NodeHuffman* node = (NodeHuffman*)malloc(sizeof(NodeHuffman));

	if (node != NULL)
	{
		node->c = list->c;
		node->nbOcc = list->nbOcc;
		node->left = NULL;
		node->right = NULL;
	}

	return node;
}

void _WriteDictionnary(NodeHuffman* tree, const char* code, FILE *dic)
{
	if (tree->c != NULL)
	{
		if (fprintf_s(dic, "%c : %s\n", tree->c, code) < 0)
		{
			printf("Error while writing in dico.txt\n\n");
		}
	}
	else
	{
		int size = strlen(code);
		if (size < 0)
		{
			printf("error to get the size of the string \"%s\"\n\n", code);
		}
		else
		{
			size += 2;
			char* nextCode = (char*)malloc(sizeof(char) * (size));
			if (nextCode == NULL)
			{
				printf("Can't allocate memory to next code in WriteDictionnary\n\n");
			}
			else
			{
				errno_t err = strcpy_s(nextCode, size, code);
				if (err)
				{
					printf("Error while copiing the old code in a new string\n\n");
				}
				else
				{
					nextCode[size - 1] = '\0';
					nextCode[size - 2] = '0';
					_WriteDictionnary(tree->left, nextCode, dic);
					nextCode[size - 2] = '1';
					_WriteDictionnary(tree->right, nextCode, dic);
				}
				free(nextCode);
			}
		}
	}
}

void WriteDictionnary(NodeHuffman* tree)
{
	printf("\nWriting dictionnary...\n");
	if (tree == NULL)
	{
		printf("The dictionnary can't be write if he is empty\n");
	}
	else
	{
		FILE *dic = NULL;
		errno_t err = fopen_s(&dic, "dico.txt", "w");

		if (err || dic == NULL)
		{
			printf("Error while opening dico.txt\n");
			PrintErrorMessageFromErrorCodeFromFile(err);
		}
		else
		{
			_WriteDictionnary(tree, "", dic);
			printf("Dictionnary writing finished...\n");
			fclose(dic);
		}
	}
}

void PrintHuffmanTree(NodeHuffman* tree)
{
	if (tree != NULL)
	{
		if (tree->c == NULL)
		{
			printf("/%d/ ", tree->nbOcc);
		}
		else
		{
			printf("%c : %d | ", tree->c, tree->nbOcc);
		}

		PrintHuffmanTree(tree->left);
		PrintHuffmanTree(tree->right);
	}
}

void FreeHuffmanTree(NodeHuffman* tree)
{
	if (tree != NULL)
	{
		FreeHuffmanTree(tree->left);
		FreeHuffmanTree(tree->right);

		free(tree);
	}
}