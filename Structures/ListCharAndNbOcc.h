#pragma once
/**
 * \file   ListCharAndNbOcc.h
 * \brief  Header of the library dedicated to the creation and allocation of characters and occurrences lists.
 *
 * \author Samy AIT-SSI samy.ait.ssi@efrei.net Alias Kapinorhm
 * \date   December 2020
*/

/**
* \typedef struct ListCharAndNbOcc
* \brief List listing the characters and their occurrences.
*/
typedef struct ListCharAndNbOcc
{
	char c;
	int nbOcc;
	struct ListCharAndNbOcc* next;
} ListCharAndNbOcc;

/**
* \brief Function for creating a node pointing at a character, its occurence and a next node. 
* \n Example :
* \code{.c}
* CreateNode('c', 'nbOcc');
* \endcode
* \param c is the character.
* \param nbOcc is the number of occurences.
* \return node.
* \return \c an error message if the node is NULL.
*/
ListCharAndNbOcc* CreateNode(char c, int nbOcc);

/**
* \brief Function for adding a new node to the characters and occurences list.
* \n Example :
* \code{.c}
* AddNodeToListCharAndNbOcc(list, 'c');
* \endcode
* \param list is the list to which the new node is added.
* \param c is the new character added of occurence equals 1.
*/
void AddNodeToListCharAndNbOcc(ListCharAndNbOcc** list, char c);

/**
* \brief Function incrementing the occurence of a listed character or adding a node for a new one to the list.
* \n Example :
* \code{.c}
* AddCharToList(list, 'c');
* \endcode
* \param list is the list where the occurence is incremented or a node for a new character is created .
* \param c is the character added to the list or whose occurrence is incremented if already listed.
*/
void AddCharToList(ListCharAndNbOcc** list, char c);

/**
* \brief Function that creates a characters and occurrences list from a file of characters.
* \n Example :
* \code{.c}
* GetListCharAndNbOccFromFile("my.file");
* \endcode
* \param path is the path to the file .
* \return list of characters and occurences.
* \return \c an error message if path to file can't be opened..
*/
ListCharAndNbOcc* GetListCharAndNbOccFromFile(char* path);