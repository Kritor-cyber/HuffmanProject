#pragma once
/**
 * \file ListCharAndNbOccFunctions.h
 * \brief Header of the library allowing to manipulate ListCharAndNbOcc structures.
 *
 * \author Ludovic LIU CHI PIOA ludovic.liu.chi.pioa@efrei.net
 * \date December 2020
 */
#include "../Structures/ListCharAndNbOcc.h"

 /**
  * \brief Function which return the sum of all the occurrence.
  *		\n Example :
  *		\code{.c}
  *		int SumOcc = GetNbOccSum(list);
  *		\endcode
  * \param list is a pointer on a list where it calculates the sum of occurrence.
  * \return the sum of occurrence in the list.
  * \return 0 if the list is NULL.
  */
int	GetNbOccSum(ListCharAndNbOcc* list);

/**
 * \brief Function to sort a list by the number of occurrence.
 *		\n Example :
 *		\code{.c}
 *		SortListCharAndNbOccCroissant(&list);
 *		\endcode
 * \param list is a double pointer on a list, will be sorted from smaller to greater number of occurrence afterward.
 */
void SortListCharAndNbOccCroissant(ListCharAndNbOcc** list);

static void _SortListCharAndNbOccCroissant(ListCharAndNbOcc** list);

/**
 * \brief Function to print a list.
 *		\n Example :
 *		\code{.c}
 *		PrintList(list);
 *		\endcode
 * \param list is a pointer on a list that will be printed on the console.
 */
void PrintList(ListCharAndNbOcc* list);

/**
 * \brief Function to free a list.
 *		\n Example :
 *		\code{.c}
 *		FreeList(list);
 *		list = NULL;
 *		\endcode
 * \param list is the pointer on the list to free, set it to NULL afterward to free cleanly the list.
 */
void FreeList(ListCharAndNbOcc* list);
