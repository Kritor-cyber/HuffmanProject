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