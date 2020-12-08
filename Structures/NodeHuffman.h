#pragma once
/**
 * \file NodeHuffman.h
 * \brief Header of the library allowing to create Huffman tree.
 * 
 * \author Ludovic LIU CHI PIOA ludovic.liu.chi.pioa@efrei.net
 * \date December 2020
 */
#include <stdio.h>
#include "ListCharAndNbOcc.h"
#include "BinaryFile.h"

/**
 * \typedef struct NodeHuffman
 * \brief a NodeHuffman is a char, an int and 2 NodeHuffman's pointers.
 */
typedef struct NodeHuffman
{
	char c; /**< the character in the text */
	int nbOcc; /**< the number of occurrence of the character */
	struct NodeHuffman* left; /**< the pointer on the left sub-tree */
	struct NodeHuffman* right; /**< the pointer on the left sub-tree */
} NodeHuffman;

/**
 * \brief Function to create a NodeHuffman with a char.
 *		\n Example :
 *		\code{.c}
 *		NodeHuffman* node = CreateNodeHuffmanFromChar(charToUse);
 *		\endcode
 * \param c is the character to use when creating the NodeHuffman.
 * \return the \c NodeHuffman's pointer if the NodeHuffman is created.
 * \return \c NULL if the NodeHuffman could not be created.
 */
NodeHuffman* CreateNodeHuffmanFromChar(char c);

/**
 * \brief Function to create a Huffman tree with a list.
 *		\n Example :
 *		\code{.c}
 *		NodeHuffman* tree = CreateHuffmanTree(list);
 *		\endcode
 * \param list is the pointer on the list used to create the Huffman tree.
 * \return a \c NodeHuffman pointer on the root of the Huffman tree if the tree could be created.
 * \return \c NULL if the Huffman tree could not be created.
 */
NodeHuffman* CreateHuffmanTree(ListCharAndNbOcc* list);

/**
 * \brief Function to create a NodeHuffman from a list.
 *		\n Example :
 *		\code{.c}
 *		NodeHuffman* node = NodeHuffmanFromNodeCharAndNbOcc(list);
 *		\endcode
 * \param list is the pointer on the list used to create the NodeHuffman.
 * \return a \c NodeHuffman pointer if the NodeHuffman could be created.
 * \return \c NULL if the NodeHuffman could not be created.
 */
NodeHuffman* NodeHuffmanFromNodeCharAndNbOcc(ListCharAndNbOcc* list);

/**
 * \brief Function to add a NodeHuffman in an array.
 *		\n Example :
 *		\code{.c}
 *		AddNodeHuffmanInArray(array, sizeArray, charOfNodeToAdd, position);
 *		\endcode
 * \param array is the double pointer on the array to modify.
 * \param arrSize is the size of the array.
 * \param car is the character to use when adding the NodeHuffman in the array.
 * \param pos is the position to add the NodeHuffman in the array.
 */
void AddNodeHuffmanInArray(NodeHuffman** array, int arrSize, char car, int pos);

/**
 * \brief Function to create an array of NodeHuffman with a file.
 *		\n Example :
 *		\code{.c}
 *		NodeHuffman** array = CreateArrayOfNodeHuffmanWithNbOccFromFile(fileToUse, sizeArray);
 *		\endcode
 * \param f is a pointer on the file to use to create the array.
 * \param SizeTab is the size of the array created.
 * \return a double pointer on a \c NodeHuffman if the array could be created.
 * \return \c NULL if the array could not be created.
 */
NodeHuffman** CreateArrayOfNodeHuffmanWithNbOccFromFile(FILE* f, int* sizeTab);

/**
 * \brief Function to create an array of NodeHuffman with a file using another method.
 *		\n Example :
 *		\code{.c}
 *		NodeHuffman** array = _CreateArrayOfNodeHuffmanWithNbOccFromFile(pathOfFile, sizeArray);
 *		\endcode
 * \param pathOfFile is a pointer to the string of the path to the file.
 * \param sizeTab is a pointer to an int of the size of the array.
 * \return a double pointer on a \c NodeHuffman if the array could be created.
 * \return \c NULL if the array could not be created.
 */
NodeHuffman** _CreateArrayOfNodeHuffmanWithNbOccFromFile(char* pathOfFile, int* sizeTab);

/**
 * \brief Function to create a Huffman tree from an array.
 *		\n Example :
 *		\code{.c}
 *		NodeHuffman* tree = CreateHuffmanTreeFromArray(array, sizeArray);
 *		\endcode
 * \param array is a double pointer on the array to use to create the Huffman tree.
 * \param size is the size of the array use to create the Hufffman tree.
 * \return the pointer of the root of the Huffman tree if the Huffman tree could be created.
 * \return \c NULL if the Huffman tree could not be created.
 */
NodeHuffman* CreateHuffmanTreeFromArray(NodeHuffman** array, int size);

/**
 * \brief Function to create a NodeHuffman with the character, the number of occurrence, the left and the right child.
 *		\n Example :
 *		\code{.c}
 *		NodeHuffman* node = CreateNodeHuffmanFromCharAndNbOccAndChilds(charToUse, nbOcc, pointerLeftChild, pointerRightChild);
 *		\endcode
 * \param car is the character to use when creating the NodeHuffman.
 * \param nbOcc is the number of occurrence to use when creating the NodeHuffman.
 * \param leftChild is the pointer on a NodeHuffman to use when creating the NodeHuffman.
 * \param rightChild is the pointer on a NodeHuffman to use when creating the NodeHuffman.
 * \return a NodeHuffman's pointer if the NodeHuffman could be created.
 * \return \c NULL if the NodeHuffman could not be created.
 */
NodeHuffman* CreateNodeHuffmanFromCharAndNbOccAndChilds(char car, int nbOcc, NodeHuffman* leftChild, NodeHuffman* rightChild);

/**
 * \brief Function to create a Huffman tree from a dictionnary file.
 *		\n Example :
 *		\code{.c}
 *		NodeHuffman* tree = CreateHuffmanTreeFromDictionnaryFile(PathToDico);
 *		\endcode
 * \param dicPath is a pointer on the string of the path to the dictionnary.
 * \return a pointer on the root of the Huffman tree if the Huffman tree could be created.
 * \return \c NULL if the Huffman tree could not be created.
 */
NodeHuffman* CreateHuffmanTreeFromDictionnaryFile(char* dicPath);

/**
 * \brief Function to create a Huffman tree from a dictionnary included in a file.
 *		\n Example :
 *		\code{.c}
 *		NodeHuffman* tree = CreateHuffmanTreeFromDictionnaryIntegratedInFile(PathToFile);
 *		\endcode
 * \param binaryFileWithDictionnary is a pointer on a BinaryFile's structure who contains the path to the file with the dictionnary.
 * \return a pointer on the root of the Huffman tree if the Huffman tree could be created.
 * \return \c NULL if the Huffman tree could not be created.
 */
NodeHuffman* CreateHuffmanTreeFromDictionnaryIntegratedInFile(BinaryFile* binaryFileWithDictionnary);