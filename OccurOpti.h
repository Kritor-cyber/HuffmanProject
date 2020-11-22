#pragma once

#include <stdio.h>
#include "Structures/NodeHuffman.h"

NodeHuffman* createNodeHuffman(char car);
void AddNodeHuffmanInArray(NodeHuffman** array, int arrSize, char car, int pos);
NodeHuffman** OccurOpti(FILE* f, int* sizeTab);
NodeHuffman** _OccurOpti(FILE* f, int* sizeTab);