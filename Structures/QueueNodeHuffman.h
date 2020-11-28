#pragma once

#include "ListHuffman.h"

typedef struct QueueNodeHuffman
{
	ListHuffman* start, *end;
	int size;
} QueueNodeHuffman;

void InitializeQueue(QueueNodeHuffman** queue);
void AddDataInQueue(QueueNodeHuffman* queue, NodeHuffman* data);
NodeHuffman* GetDataFromQueueNodeHuffman(QueueNodeHuffman* queue);