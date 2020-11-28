#include "NodeAVLDictionnaryFunctions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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