#pragma once

#include "NodeHuffman.h"

typedef struct ListHuffman
{
	NodeHuffman* data;
	struct ListHuffman* next;
} ListHuffman;

ListHuffman* CreateNodeListHuffman(NodeHuffman* data);
void AddToListHuffman(ListHuffman** list, NodeHuffman* node);