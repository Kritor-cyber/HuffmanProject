#pragma once
/**
 * \file NodeHuffmanFunctions.h
 * \brief Header of the library allowing to manipulate structures based on NodeHuffman.
 *
 * \author Ludovic LIU CHI PIOA ludovic.liu.chi.pioa@efrei.net
 * \date December 2020
 */
#include <stdio.h>
#include "../Structures/NodeHuffman.h"
#include "../Structures/QueueNodeHuffman.h"

static void _WriteDictionnary(NodeHuffman* tree, const char* code, FILE* dic);

 /**
  * \brief Function to create the dictionnary from the Huffman tree.
  *		\n Example :
  *		\code{.c}
  *		WriteDictionnary(tree);
  *		\endcode
  * \param tree is a pointer on the Huffman tree to use to create the dictionnary.
  */
void WriteDictionnary(NodeHuffman* tree);

/**
 * \brief Function to print the Huffman tree.
 *		\n Example :
 *		\code{.c}
 *		PrintHuffmanTree(tree);
 *		\endcode
 * \param tree is the pointer on the Huffman tree to print.
 */
void PrintHuffmanTree(NodeHuffman* tree);

/**
 * \brief Function to free the memory of the Huffman tree.
 *		\n Example :
 *		\code{.c}
 *		FreeHuffmanTree(tree);
 *		\endcode
 * \param tree is the pointer on the Huffman tree to free.
 */
void FreeHuffmanTree(NodeHuffman* tree);

static int IsSuperior(const NodeHuffman** noeud1, const NodeHuffman** noeud2);

/**
 * \brief Function to sort an array by number of occurrence.
 *		\n Example :
 *		\code{.c}
 *		SortArrayByNbOcc(&array, sizeArray);
 *		\endcode
 * \param array is a double pointer on the array to sort.
 * \param size is the size of the array.
 */
void SortArrayByNbOcc(NodeHuffman** array, int size);

/**
 * \brief Function to divide an array into 2 queue.
 *		\n Example :
 *		\code{.c}
 *		UpdateArrayNextHuffmanNodes(&array, sizeArray, queue1, queue2);
 *		\endcode
 * \param array is a double pointer on an array of NodeHuffman.
 * \param size is the size of the array.
 * \param l1 is a pointer on a structure QueueNodeHuffman.
 * \param l2 is a pointer on a structure QueueNodeHuffman.
 */
void UpdateArrayNextHuffmanNodes(NodeHuffman** array, int size, QueueNodeHuffman* l1, QueueNodeHuffman* l2);

/**
 * \brief Function to return the NodeHuffman with the less number of occurrence from an array.
 *		\n Example :
 *		\code{.c}
 *		NodeHuffman* node = GetMinNodeFromArray(&array, sizeArray);
 *		\endcode
 * \param array is a double pointer on an array of NodeHuffman.
 * \param size is the size of the array.
 * \return a pointer on the NodeHuffman with the less number of occurrence.
 * \return \c NULL if their is an error.
 */
NodeHuffman* GetMinNodeFromArray(NodeHuffman** array, int size);

/**
 * \brief Function to remove a NodeHuffman from an array.
 *		\n Example :
 *		\code{.c}
 *		RemoveNodeFromArray(&array, sizeArray, nodeToRemove);
 *		\endcode
 * \param array is a double pointer on an array of NodeHuffman.
 * \param size is the size of the array.
 * \param nodeToRemove is the pointer on the NodeHuffman to remove.
 */
void RemoveNodeFromArray(NodeHuffman** array, int size, NodeHuffman* nodeToRemove);

/**
 * \brief Function to add a NodeHuffman to a Huffman tree.
 *		\n Example :
 *		\code{.c}
 *		AddNodeHuffmanInHuffmanTree(&tree, charToUse, code);
 *		\endcode
 * \param tree is a double pointer of a Huffman tree.
 * \param c is the character to add in the Huffman tree.
 * \param code is a pointer an string containing the code of the character.
 */
void AddNodeHuffmanInHuffmanTree(NodeHuffman** tree, char c, char* code);