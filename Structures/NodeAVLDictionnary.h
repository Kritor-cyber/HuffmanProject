#pragma once
/**
 * \file   NodeAVLDictionnary.h
 * \brief  Header of the library dedicated to the creation and memory allocation of the AVL dictionnary.
 *
 * \author Samy AIT-SSI samy.ait.ssi@efrei.net Alias Kapinorhm
 * \date   December 2020
*/

#include "NodeHuffman.h"

/**
* \typedef struct NodeAVLDictionnary
* \brief structur of the AVL Dictionnary node, with pointing at a character, its code and two AVL Dictionnary nodes.
*/
typedef struct NodeAVLDictionnary
{
	char c;
	char* code;
	struct NodeAVLDictionnary* left;
	struct NodeAVLDictionnary* right;
} NodeAVLDictionnary;

/**
* \brief Function that creates an AVL Dictionnary Node.
* \n Example :
* \code{.c}
* AddNodeInNodeDictionnary(&dictionnary, 'c', code);
* \endcode
* \param dic is the pointer and new node added to the AVL Dictionnary.
* \param c is the character affected and pointed by dic.
* \param code is the binary suit affected to the character and pointed by dic.
*/
void AddNodeInNodeDictionnary(NodeAVLDictionnary** dic, char c, char* code);

/**
* \brief Function that creates and shows an AVL Dictionnary using a Huffman tree.
* \n Example :
* \code{.c}
* CreateAVLDictionnaire(tree);
* \endcode
* \param tree is the Huffman tree we are using to create the AVL Dictionnary .
* \return an AVL Dictionnary node.
*/
NodeAVLDictionnary* CreateAVLDictionnary(NodeHuffman* tree);

/**
* \brief Function that copies the new code into the AVLDictionnary and creates an AVL Dictionnary node if current node is an external node.
* \n Example :
* \code{.c}
* _CreateAVLDictionnary(node, code, whole_number, tree);
* \endcode
* \param actualNode is the current node the function uses.
* \param code is the character's code.
* \param codeSize is the size of the character's code.
* \param tree is the AVLDictionnary tree node the function uses.
*/
void _CreateAVLDictionnary(NodeHuffman* actualNode, char* code, int codeSize, NodeAVLDictionnary** tree);

/**
* \brief Function that returns a character code from the AVL Dictionnary.
* \n Example :
* \code{.c}
* GetCharCodeFromAVLDic(dictionnary, 'c');
* \endcode
* \param dic is the AVLDictionnary pointing at the characters and the codes.
* \param c is the character the function searches the code for.
* \return the code of the character.
*/
char* GetCharCodeFromAVLDic(NodeAVLDictionnary* dic, char c);