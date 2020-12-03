#pragma once
/**
 * \file ListCharAndNbOccFunctions.h
 * \brief Header of the library allowing .
 *
 * \author Ludovic LIU CHI PIOA ludovic.liu.chi.pioa@efrei.net
 * \date December 2020
 */
#include "../Structures/ListCharAndNbOcc.h"

 /**
  * \brief Function which return the sum of all the occurrence.
  *		\n Example :
  *		\code{.c}
  *		int SumOcc = GetNbOccSum(list)
  *		\endcode
  * \param list is a pointer on a list.
  * \return the sum of occurrence in the list.
  * \return 0 if the list is NULL.
  */
int	GetNbOccSum(ListCharAndNbOcc* list);

/**
 * \brief Function to sort a list by the number of occurrence.
 * \param list is a double pointer on a list.
 */
void SortListCharAndNbOccCroissant(ListCharAndNbOcc** list);

/**
 * \brief Function to manipulate a list and sort it by the number of occurrence.
 * \param list is a double pointer on a list.
 */
static void _SortListCharAndNbOccCroissant(ListCharAndNbOcc** list);

/**
 * \brief Function to print a list.
 * \param list is a pointer on a list.
 */
void PrintList(ListCharAndNbOcc* list);

/**
 * \brief Function to free a list.
 * \param list is a pointer on a list.
 */
void FreeList(ListCharAndNbOcc* list);