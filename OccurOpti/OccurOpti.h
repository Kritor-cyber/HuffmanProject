#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeHuffman {
	char c;
	int nbOcc;
	struct NodeHuffman* left;
	struct NodeHuffman* right;
}NodeHuffman;

NodeHuffman* createNodeHuffman(char car);
void AddNodeHuffmanInArray(NodeHuffman** array, int arrSize, char car, int pos);
NodeHuffman** OccurOpti(FILE* f, int* sizeTab);