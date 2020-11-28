#pragma once

#include <stdio.h>
#include "../Structures/NodeHuffman.h"
#include "../Structures/QueueNodeHuffman.h"

void WriteDictionnary(NodeHuffman* tree);
void PrintHuffmanTree(NodeHuffman* tree);
void FreeHuffmanTree(NodeHuffman* tree);

void SortArrayByNbOcc(NodeHuffman** array, int size);

NodeHuffman* GetMinNodeFromArray(NodeHuffman** array, int size);
void RemoveNodeFromArray(NodeHuffman** array, int size, NodeHuffman* nodeToRemove);
void UpdateArrayNextHuffmanNodes(NodeHuffman** array, int size, QueueNodeHuffman* l1, QueueNodeHuffman* l2);

void AddNodeHuffmanInHuffmanTree(NodeHuffman** tree, char c, char* code);