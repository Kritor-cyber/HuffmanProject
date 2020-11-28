#pragma once

#include "../Structures/ListCharAndNbOcc.h"

int	GetNbOccSum(ListCharAndNbOcc* list);
void SortListCharAndNbOccCroissant(ListCharAndNbOcc** list);
static void _SortListCharAndNbOccCroissant(ListCharAndNbOcc** list);

void PrintList(ListCharAndNbOcc* list);
void FreeList(ListCharAndNbOcc* list);