#pragma once

typedef struct ListCharAndNbOcc
{
	char c;
	int nbOcc;
	struct ListCharAndNbOcc* next;
} ListCharAndNbOcc;

ListCharAndNbOcc* CreateNode(char c, int nbOcc);
void AddNodeToListCharAndNbOcc(ListCharAndNbOcc** list, char c);
void AddCharToList(ListCharAndNbOcc** list, char c);

void FreeList(ListCharAndNbOcc* list);

ListCharAndNbOcc* GetListCharAndNbOccFromFile(char* path);