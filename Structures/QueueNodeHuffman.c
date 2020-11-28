#include "QueueNodeHuffman.h"

#include <stdio.h>

void InitializeQueue(QueueNodeHuffman** queue)
{
	if (*queue == NULL)
	{
		(*queue) = (QueueNodeHuffman*)malloc(sizeof(QueueNodeHuffman));
		(*queue)->start = NULL;
		(*queue)->end = NULL;
		(*queue)->size = 0;
	}
}

void AddDataInQueue(QueueNodeHuffman* queue, NodeHuffman* data)
{
	if (queue != NULL)
	{
		if (queue->size == 0)
		{
			queue->start = (ListHuffman*)malloc(sizeof(ListHuffman));
			queue->start->data = data;
			queue->start->next = NULL;
			queue->end = queue->start;
		}
		else
		{
			queue->end->next = (ListHuffman*)malloc(sizeof(ListHuffman));
			queue->end = queue->end->next;
			queue->end->data = data;
			queue->end->next = NULL;
		}

		queue->size++;
	}
}

NodeHuffman* GetDataFromQueueNodeHuffman(QueueNodeHuffman* queue)
{
	if (queue->size == 0)
		return NULL;
	else
	{
		queue->size--;
		NodeHuffman* nodeToReturn = queue->start->data;
		ListHuffman* oldStart = queue->start;
		queue->start = queue->start->next;
		free(oldStart);
		return nodeToReturn;
	}
}