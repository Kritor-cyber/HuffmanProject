#pragma once

#include "ListCharAndNbOcc.h"

typedef struct NodeHuffman
{
	char c;
	int nbOcc;
	struct NodeHuffman* left;
	struct NodeHuffman* right;
} NodeHuffman;

NodeHuffman* CreateHuffmanTree(ListCharAndNbOcc* list);
NodeHuffman* NodeHuffmanFromNodeCharAndNbOcc(ListCharAndNbOcc* list);

void WriteDictionnary(NodeHuffman* tree);

void PrintHuffmanTree(NodeHuffman* tree);
void FreeHuffmanTree(NodeHuffman* tree);

void SortArrayByNbOcc(NodeHuffman** array, int size);
NodeHuffman* CreateNodeHuffmanFromCharAndNbOccAndChilds(char car, int nbOcc, NodeHuffman* leftChild, NodeHuffman* rightChild);
NodeHuffman* CreateHuffmanTreeFromArray(NodeHuffman** array, int size);

NodeHuffman* GetMinNodeFromArray(NodeHuffman** array, int size);
void RemoveNodeFromArray(NodeHuffman** array, int size, NodeHuffman* nodeToRemove);
void UpdateArrayNextHuffmanNodes(NodeHuffman** array, int size, void* l1, void* l2);