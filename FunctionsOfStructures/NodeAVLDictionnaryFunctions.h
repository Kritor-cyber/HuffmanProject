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
  * \param tree is a pointer on an AVL.
  * \return the depth of the AVL.
  * \return -1 if the AVL is NULL.
  */
int _AVLDepth(NodeAVLDictionnary* tree);

/**
 * \brief Function which return the balance factor of an AVL.
 *		\n Example :
 *		\code{.c}
 *		int balanceFactor = _AVLBalanceFactor(tree);
 *		\endcode
 * \param tree is a pointer on an AVL.
 * \return the balance factor of the AVL.
 * \return 0 if the AVL is NULL.
 */
int _AVLBalanceFactor(NodeAVLDictionnary* tree);

/**
 * \brief Function to do a right rotation on an AVL.
 * \param tree is a pointer on an AVL.
 */
void _AVLRightRotation(NodeAVLDictionnary** tree);

/**
 * \brief Function to do a left rotation on an AVL.
 * \param tree is a pointer on an AVL.
 */
void _AVLLeftRotation(NodeAVLDictionnary** tree);

/**
 * \brief Function to balance an AVL.
 * \param tree is a pointer on an AVL.
 */
void AVLBalance(NodeAVLDictionnary** tree);

/**
 * \brief Function to print an AVL.
 * \param tree is a pointer on an AVL.
 */
void PrintNodeAVLDictionnary(NodeAVLDictionnary* tree);

/**
 * \brief Function to free an AVL.
 * \param tree is a pointer on an AVL.
 */
void FreeNodeAVLDictionnary(NodeAVLDictionnary* tree);