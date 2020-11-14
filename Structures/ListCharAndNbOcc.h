#pragma once

typedef struct ListCharAndNbOcc
{
	char c;
	int nbOcc;
	struct ListCharAndNbOcc* next;
} ListCharAndNbOcc;

ListCharAndNbOcc*	CreateNode					(char c, int nbOcc);
void				AddNodeToListCharAndNbOcc	(ListCharAndNbOcc** list, char c);
void				AddCharToList				(ListCharAndNbOcc** list, char c);

int		GetNbOccSum(ListCharAndNbOcc* list);
void	SortListCharAndNbOccCroissant(ListCharAndNbOcc** list);
static void _SortListCharAndNbOccCroissant(ListCharAndNbOcc** list);

void PrintList(ListCharAndNbOcc* list);
void FreeList(ListCharAndNbOcc* list);