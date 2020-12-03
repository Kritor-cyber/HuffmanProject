#pragma once
/**
 * \file NodeAVLDictionnaryFunctions.h
 * \brief Header of the library allowing to manipulate an AVL tree.
 *
 * \author Ludovic LIU CHI PIOA ludovic.liu.chi.pioa@efrei.net
 * \date December 2020
 */
#include "../Structures/NodeAVLDictionnary.h"

// Functions used to equilibrate the AVL

 /**
  * \brief Function which return the depth of an AVL.
  *		\n Example :
  *		\code{.c}
  *		int depth = _AVLDepth(tree);
  *		\endcode
  * \param tree is a pointer on the AVL where it search the depth.
  * \return the depth of the AVL.
  * \return -1 if the AVL is NULL.
  */
static int _AVLDepth(NodeAVLDictionnary* tree);

/**
 * \brief Function which return the balance factor of an AVL.
 *		\n Example :
 *		\code{.c}
 *		int balanceFactor = _AVLBalanceFactor(tree);
 *		\endcode
 * \param tree is a pointer on the AVL where it calculates the balance factor.
 * \return the balance factor of the AVL.
 * \return 0 if the AVL is NULL.
 */
static int _AVLBalanceFactor(NodeAVLDictionnary* tree);

/**
 * \brief Function to do a right rotation on an AVL.
 *		\n Example :
 *		\code{.c}
 *		_AVLRightRotation(&tree);
 *		\endcode
 * \param tree is a double pointer on the AVL where it does a right rotation.
 */
static void _AVLRightRotation(NodeAVLDictionnary** tree);

/**
 * \brief Function to do a left rotation on an AVL.
 *		\n Example :
 *		\code{.c}
 *		_AVLLeftRotation(&tree);
 *		\endcode
 * \param tree is a pointer on the AVL where it does a left rotation.
 */
static void _AVLLeftRotation(NodeAVLDictionnary** tree);

/**
 * \brief Function to balance an AVL.
 *		\n Example :
 *		\code{.c}
 *		AVLBalance(&tree);
 *		\endcode
 * \param tree is a pointer on the AVL it will balances.
 */
void AVLBalance(NodeAVLDictionnary** tree);

/**
 * \brief Function to print an AVL.
 *		\n Example :
 *		\code{.c}
 *		PrintNodeAVLDictionnary(tree);
 *		\endcode
 * \param tree is a pointer on an AVL that will be printed on the console.
 */
void PrintNodeAVLDictionnary(NodeAVLDictionnary* tree);

/**
 * \brief Function to free an AVL.
 *		\n Example :
 *		\code{.c}
 *		FreeNodeAVLDictionnary(tree);
 *		tree = NULL;
 *		\endcode
 * \param tree is the pointer on the AVL tree to free, set it to NULL afterward to free cleanly the tree.
 */
void FreeNodeAVLDictionnary(NodeAVLDictionnary* tree);