#include "NodeHuffmanFunctions.h"

#include "../Structures/ListHuffman.h"
#include "../Utilities.h"

#include <stdlib.h>
#include <string.h>

static void _WriteDictionnary(NodeHuffman* tree, const char* code, FILE *dic)
{
	if (tree->c != '\0')
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
		FILE* dic = NULL;
		errno_t err = fopen_s(&dic, "dico.txt", "wb");

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
		if (tree->c == '\0')
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
 
static int IsSuperior(const NodeHuffman** noeud1, const NodeHuffman** noeud2)
{
	if ((*noeud1)->nbOcc < (*noeud2)->nbOcc) return -1;
	if ((*noeud1)->nbOcc > (*noeud2)->nbOcc) return 1;
	return 0;
}

void SortArrayByNbOcc(NodeHuffman** array, int size)
{
	qsort(array, size, sizeof(NodeHuffman*), IsSuperior);
}

void UpdateArrayNextHuffmanNodes(NodeHuffman** array, int size, QueueNodeHuffman* l1, QueueNodeHuffman* l2)
{
	for (int i = 0; i < 4; i++)
	{
		if (array[i] == NULL)
		{
			if (i < 2)
			{
				array[i] = GetDataFromQueueNodeHuffman(l1);
			}
			else
			{
				array[i] = GetDataFromQueueNodeHuffman(l2);
			}
		}
	}
}

NodeHuffman* GetMinNodeFromArray(NodeHuffman** array, int size)
{
	NodeHuffman* minNode = NULL;

	for (int i = 0; i < size; i++)
	{
		if (array[i] != NULL && (minNode == NULL || minNode->nbOcc > array[i]->nbOcc))
		{
			minNode = array[i];
		}
	}

	return minNode;
}

void RemoveNodeFromArray(NodeHuffman** array, int size, NodeHuffman* nodeToRemove)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == nodeToRemove)
		{
			array[i] = NULL;
		}
	}
}

void AddNodeHuffmanInHuffmanTree(NodeHuffman** tree, char c, char* code)
{
	if (*tree == NULL)
	{
		(*tree) = CreateNodeHuffmanFromChar('\0');
	}

	if (*tree != NULL)
	{
		if (code != NULL)
		{
			if (code[0] == '\0')
			{
				(*tree)->c = c;
				(*tree)->nbOcc = 1;
			}
			else if (code[0] == '1')
			{
				AddNodeHuffmanInHuffmanTree(&((*tree)->right), c, code + 1);
			}
			else if (code[0] == '0')
			{
				AddNodeHuffmanInHuffmanTree(&((*tree)->left), c, code + 1);
			}
		}
	}
}