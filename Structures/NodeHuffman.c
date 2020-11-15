#include "NodeHuffman.h"

#include "ListHuffman.h"

#include <stdlib.h>

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