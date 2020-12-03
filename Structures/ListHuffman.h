#pragma once
/**
 * \file   ListHuffman.h
 * \brief  Header of the library dedicated to the creation, allocation and deallocation of Huffman lists. 
 *
 * \author Samy AIT-SSI samy.ait.ssi@efrei.net Alias Kapinorhm
 * \date   December 2020
*/

#include "NodeHuffman.h"

/**
* \typedef struct ListHuffman
* \brief a Huffman list structur containing a data and pointing to a next Huffman list.
*/
typedef struct ListHuffman
{
	NodeHuffman* data;
	struct ListHuffman* next;
} ListHuffman;

/**
* \brief Function that creates a Huffman list node.
* \n Example :
* \code{.c}
* CreateNodeListHuffman(data);
* \endcode
* \param data is the information to put inside the Huffman list node.
* \return the node.
*/
ListHuffman* CreateNodeListHuffman(NodeHuffman* data);

/**
* \brief Function that adds a new node to the Huffman list.
* \n Example :
* \code{.c}
* AddToListHuffman(&list, nodeToAdd);
* \endcode
* \param list ist the Huffman list to which the nodeToAdd is added.
* \param nodeToAdd is the node to add to the Huffman list.
*/
void AddToListHuffman(ListHuffman** list, NodeHuffman* nodeToAdd);

/**
* \brief Function that deallocates the memory allocated to the Huffman list.
* \n Example :
* \code{.c}
* FreeListHuffman(list);
* \endcode
* \param list is the Huffman list to deallocate.
*/
void FreeListHuffman(ListHuffman* list);