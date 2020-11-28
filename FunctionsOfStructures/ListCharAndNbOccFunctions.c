#include "ListCharAndNbOccFunctions.h"

#include <stdio.h>

#define DEBUG 0

int GetNbOccSum(ListCharAndNbOcc* list)
{
	if (list == NULL)
		return 0;
	else
		return GetNbOccSum(list->next) + list->nbOcc;
}

void SortListCharAndNbOccCroissant(ListCharAndNbOcc** list)
{
	if (list != NULL && *list != NULL)
	{
		char sorted = 0;
		ListCharAndNbOcc* tmp;

		while (!sorted)
		{
			sorted = 1;
			tmp = *list;

			while (tmp != NULL && tmp->next != NULL)
			{
				if (tmp->nbOcc > tmp->next->nbOcc)
				{
					sorted = 0;
					_SortListCharAndNbOccCroissant(list);
				}
				tmp = tmp->next;
			}
		}
	}
}

static void _SortListCharAndNbOccCroissant(ListCharAndNbOcc** list)
{
	if (list == NULL || *list == NULL || (*list)->next == NULL)
		return 0;

	ListCharAndNbOcc* chr = *list;

	if (chr->nbOcc > chr->next->nbOcc)
	{
		ListCharAndNbOcc* temp = chr->next;
		chr->next = chr->next->next;
		temp->next = chr;
		*list = temp;
		chr = *list;
	}

	_SortListCharAndNbOccCroissant(&(chr->next));
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

void FreeList(ListCharAndNbOcc* list)
{
	if (list != NULL)
	{
		FreeList(list->next);
		free(list);
	}
}