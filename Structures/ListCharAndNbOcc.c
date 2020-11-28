#include "ListCharAndNbOcc.h"

#include <stdio.h>

#define DEBUG 0

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

ListCharAndNbOcc* GetListCharAndNbOccFromFile(char* path)
{
	FILE* fileToRead;
	errno_t err = fopen_s(&fileToRead, path, "r");

	if (DEBUG) printf("chemin vers le fichier a ouvrir : %s\n", path);

	if (err || fileToRead == NULL)
	{
		printf("Can't open file \"%s\"\n", path);

		PrintErrorMessageFromErrorCodeFromFile(err);

		return NULL;
	}
	else
	{
		char c;
		ListCharAndNbOcc* list = NULL;
		while ((c = getc(fileToRead)) != EOF)
		{
			AddCharToList(&list, c);
		}

		fclose(fileToRead);

		if (list != NULL)
		{
			return list;
		}
	}

	return NULL;
}