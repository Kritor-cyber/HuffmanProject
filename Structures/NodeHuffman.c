#include "NodeHuffman.h"

#include "ListHuffman.h"
#include "../Utilities.h"
#include "QueueNodeHuffman.h"
#include "../FunctionsOfStructures/ListCharAndNbOccFunctions.h"

#include <stdlib.h>
#include <string.h>

NodeHuffman* CreateNodeHuffmanFromChar(char c)
{
	NodeHuffman* node = (NodeHuffman*)malloc(sizeof(NodeHuffman));

	if (node == NULL)
		printf("can’t allocate memory to NodeHuffman in createNodeHuffman()\n");
	else {
		node->c = c;
		node->nbOcc = 1;
		node->left = NULL;
		node->right = NULL;
	}

	return node;
}

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
				nextNode->c = '\0';
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

void AddNodeHuffmanInArray(NodeHuffman** array, int arrSize, char car, int pos)
{
	if (array[pos] != NULL)
	{
		for (int i = arrSize; i > pos; i--)
			array[i] = array[i - 1];
	}

	array[pos] = CreateNodeHuffmanFromChar(car);
}

NodeHuffman** CreateArrayOfNodeHuffmanWithNbOccFromFile(FILE* f, int* sizeTab)
{
	NodeHuffman** tab = (NodeHuffman**)calloc(256, sizeof(NodeHuffman*));

	fseek(f, 0, SEEK_SET);

	if (tab == NULL)
		printf("can’t allocate memory to array NodeHuffman in OccurOpti()\n");
	else
	{
		char car;
		int start, end, mid, found;
		int tabOcc[256] = { 0 };
		*sizeTab = 0;

		while ((car = fgetc(f)) != EOF)
		{
			start = 0;
			end = *sizeTab;
			found = 0;
			mid = 0;

			while (found == 0 && start <= end) {
				mid = (start + end) / 2;

				if (tab[mid] != NULL) {
					if (tab[mid]->c == car)
						found = 1;
					else if (car > tab[mid]->c)
						start = mid + 1;
					else
						end = mid - 1;
				}
				else
					start = end + 1;
			}

			if (found != 0)
				tab[mid]->nbOcc++;
			else {
				if (tab[mid] != NULL && car > tab[mid]->c)
					mid++;

				AddNodeHuffmanInArray(tab, *sizeTab, car, mid);
				*sizeTab = *sizeTab + 1;
			}
		}
	}
	return tab;
}

NodeHuffman** _CreateArrayOfNodeHuffmanWithNbOccFromFile(char* pathOfFile, int* sizeTab)
{
	FILE* f = NULL;
	errno_t err = fopen_s(&f, pathOfFile, "r");
	if (err || f == NULL)
	{
		printf("There is an error while opening the file %s\n", pathOfFile);
		PrintErrorMessageFromErrorCodeFromFile(err);
	}
	else
	{
		char car;
		int tabOcc[256] = { 0 };
		(*sizeTab) = 0;
		ListCharAndNbOcc* list = NULL;
		while ((car = fgetc(f)) != EOF)
		{
			tabOcc[car]++;
			if (tabOcc[car] == 1)
			{
				(*sizeTab) += 1;
			}
		}
		NodeHuffman** tab = (NodeHuffman**)malloc(*sizeTab * sizeof(NodeHuffman*));
		int i = 0;
		car = 0;
		while (i < *sizeTab)
		{
			while (tabOcc[car] == 0)
			{
				car++;
			}
			tab[i] = CreateNodeHuffmanFromChar(car);
			tab[i]->nbOcc = tabOcc[car];
			i++;
			car++;
		}
		FreeList(list);
		fclose(f);
		return tab;
	}
	
	return NULL;
}

NodeHuffman* CreateHuffmanTreeFromArray(NodeHuffman** array, int size)
{
	if (size == 0)
	{
		printf("t (%d) can't be less than 1\n", size);
	}
	else
	{
		NodeHuffman* nodes[4] = { NULL, NULL, NULL, NULL };
		NodeHuffman* nodeMin1 = NULL;
		NodeHuffman* nodeMin2 = NULL;
		NodeHuffman* newNode = NULL;
		QueueNodeHuffman* list = NULL;
		QueueNodeHuffman* listNodeHuffmanTree = NULL;
		InitializeQueue(&list);
		InitializeQueue(&listNodeHuffmanTree);
		if (list == NULL || listNodeHuffmanTree == NULL)
		{
			printf("failed to initialize list or listNodeHuffmanTree in CreateHuffmanTreeFromArray in NodeHuffman.c\n");
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				AddDataInQueue(list, array[i]);
			}

			while (list->size + listNodeHuffmanTree->size > 1)
			{
				UpdateArrayNextHuffmanNodes(nodes, 4, list, listNodeHuffmanTree);
				nodeMin1 = GetMinNodeFromArray(nodes, 4);
				RemoveNodeFromArray(nodes, 4, nodeMin1);
				nodeMin2 = GetMinNodeFromArray(nodes, 4);
				RemoveNodeFromArray(nodes, 4, nodeMin2);

				newNode = CreateNodeHuffmanFromCharAndNbOccAndChilds('\0', nodeMin1->nbOcc + nodeMin2->nbOcc, nodeMin1, nodeMin2);
				AddDataInQueue(listNodeHuffmanTree, newNode);
			}

			if (list->size != 0)
			{
				printf("Strange, how can this happen ?? (NodeHuffman.c in CreateHuffmanTreeFromArray()\n");
				NodeHuffman* huffmanTreeToReturn = GetDataFromQueueNodeHuffman(list);
				FreeQueueNodeHuffman(list);
				FreeQueueNodeHuffman(listNodeHuffmanTree);
				return huffmanTreeToReturn;
			}
			else
			{
				NodeHuffman* huffmanTreeToReturn = GetDataFromQueueNodeHuffman(listNodeHuffmanTree);
				FreeQueueNodeHuffman(list);
				FreeQueueNodeHuffman(listNodeHuffmanTree);
				return huffmanTreeToReturn;
			}

			FreeQueueNodeHuffman(listNodeHuffmanTree);
		}
	}

	return NULL;
}

NodeHuffman* CreateNodeHuffmanFromCharAndNbOccAndChilds(char car, int nbOcc, NodeHuffman* leftChild, NodeHuffman* rightChild)
{
	NodeHuffman* node = (NodeHuffman*)malloc(sizeof(NodeHuffman));

	if (node != NULL)
	{
		node->c = car;
		node->nbOcc = nbOcc;
		node->left = leftChild;
		node->right = rightChild;
	}

	return node;
}

NodeHuffman* CreateHuffmanTreeFromDictionnaryFile(char* dicPath)
{
	if (dicPath != NULL)
	{
		FILE* dic = NULL;
		errno_t err = fopen_s(&dic, dicPath, "r");

		if (err || dic == NULL)
		{
			PrintErrorMessageFromErrorCodeFromFile(err);
			return NULL;
		}
		else
		{
			NodeHuffman* tree = NULL;
			char c, oldC = '\0';

			while ((c = fgetc(dic)) != EOF)
			{
				fgetc(dic);
				fgetc(dic);
				fgetc(dic);

				char* code = (char*)malloc(sizeof(char));
				char* newCode = NULL;
				if (code == NULL)
				{
					printf("Can't allocate memory to code in CreateDictionnaryNodeAVLDictionnary() in Dictionnary.c\n");
				}
				else
				{
					int codeSize = 1;
					oldC = c;

					while ((c = fgetc(dic)) != '\n')
					{
						codeSize++;
						newCode = (char*)realloc(code, sizeof(char) * codeSize);
						if (newCode == NULL)
						{
							printf("Can't reallocate memory to code in CreateDictionnaryNodeAVLDictionnary() in Dictionnary.c\n");
							codeSize = 0;
						}
						else
						{
							code = newCode;
							code[codeSize - 2] = c;
						}
					}

					if (code != NULL)
					{
						code[codeSize - 1] = '\0';
						AddNodeHuffmanInHuffmanTree(&tree, c, code);
					}
				}
			}

			return tree;
		}
	}

	return NULL;
}