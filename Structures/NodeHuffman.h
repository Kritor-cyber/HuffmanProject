#pragma once

#include <stdio.h>
#include "ListCharAndNbOcc.h"
#include "BinaryFile.h"

typedef struct NodeHuffman
{
	char c;
	int nbOcc;
	struct NodeHuffman* left;
	struct NodeHuffman* right;
} NodeHuffman;

NodeHuffman* CreateNodeHuffmanFromChar(char c);
NodeHuffman* CreateHuffmanTree(ListCharAndNbOcc* list);
NodeHuffman* NodeHuffmanFromNodeCharAndNbOcc(ListCharAndNbOcc* list);
void AddNodeHuffmanInArray(NodeHuffman** array, int arrSize, char car, int pos);
NodeHuffman** CreateArrayOfNodeHuffmanWithNbOccFromFile(FILE* f, int* sizeTab);

NodeHuffman** _CreateArrayOfNodeHuffmanWithNbOccFromFile(char* pathOfFile, int* sizeTab);

NodeHuffman* CreateNodeHuffmanFromCharAndNbOccAndChilds(char car, int nbOcc, NodeHuffman* leftChild, NodeHuffman* rightChild);
NodeHuffman* CreateHuffmanTreeFromArray(NodeHuffman** array, int size);

NodeHuffman* CreateHuffmanTreeFromDictionnaryFile(char* dicPath);

NodeHuffman* CreateHuffmanTreeFromDictionnaryIntegratedInFile(BinaryFile* binaryFileWithDictionnary);