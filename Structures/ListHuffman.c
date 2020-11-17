#include "ListHuffman.h"

#include <stdlib.h>

ListHuffman* CreateNodeListHuffman(NodeHuffman* data)
{
	ListHuffman* node = (ListHuffman*)malloc(sizeof(ListHuffman));
	if (node == NULL)
	{
		perror("Can't allocate memory for new node");
	}
	else
	{
		node->data = data;
		node->next = NULL;
	}

	return node;
}

void AddToListHuffman(ListHuffman** list, NodeHuffman* nodeToAdd)
{
	if (*list == NULL)
	{
		*list = CreateNodeListHuffman(nodeToAdd);
	}
	else
	{
		ListHuffman* temp = *list;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = CreateNodeListHuffman(nodeToAdd);
	}
}