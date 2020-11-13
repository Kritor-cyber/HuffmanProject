#include "ListCharAndNbOcc.h"

#include <stdio.h>

ListCharAndNbOcc* CreateNode(char c, int nbOcc)
{
	ListCharAndNbOcc* node = (ListCharAndNbOcc*)malloc(sizeof(ListCharAndNbOcc));
	if (node == NULL)
	{
		perror("Can't allocate memory for new node");
	}
	else
	{
		node->c = c;
		node->nbOcc = nbOcc;
		node->next = NULL;
	}

	return node;
}

void AddNodeToListCharAndNbOcc(ListCharAndNbOcc** list, char c)
{
	if (*list == NULL)
	{
		*list = CreateNode(c, 1);
	}
	else
	{
		ListCharAndNbOcc* temp = *list;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = CreateNode(c, 1);
	}
}

void AddCharToList(ListCharAndNbOcc** list, char c)
{
	ListCharAndNbOcc* temp = *list;
	char find = 0;
	while (temp != NULL && !find)
	{
		if (temp->c == c)
		{
			temp->nbOcc++;
			find = 1;
		}
		else
		{
			temp = temp->next;
		}
	}

	if (!find)
	{
		AddNodeToListCharAndNbOcc(list, c);
	}
}

void PrintList(ListCharAndNbOcc* list)
{
	while (list != NULL)
	{
		printf("(%c : %d) -> ", list->c, list->nbOcc);
		list = list->next;
	}

	printf("\n\n");
}

int GetNbOccSum(ListCharAndNbOcc* list)
{
	if (list == NULL)
		return 0;
	else
		return GetNbOccSum(list->next) + list->nbOcc;
}

void FreeList(ListCharAndNbOcc* list)
{
	if (list != NULL)
	{
		FreeList(list->next);
		free(list);
	}
}