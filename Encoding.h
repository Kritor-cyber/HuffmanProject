#pragma once

/**
 * \file   Encoding.h
 * \brief  Header of the library allowing to compress an ASCII file.
 *
 * \author Thibault DENIER thibault.denier@efrei.net Alias Kritor-cyber
 * \date   December 2020
*/

#include "Structures/NodeAVLDictionnary.h"

#include <stdio.h>
#include "Structures/BinaryFile.h"

/**
 * \brief Function to write the compress file.
 * \n Example:
 * \code{.c}
 * BinaryFile* compressedFile = OpenBinaryFile("Alice.txt");
 * NodeAVLDictionnary* dictionnary = CreerAVLDictionnaire(array);
 * 
 * EncodeFileAVLTree("Alice.txt", compressedFile, dictionnary);
 * \endcode
 * \param pathOfFileToCompress is the path (string NULL terminated byte) of the file you want to compress.
 * \param compressedFile is a pointer to a \c BinaryFile open in "wb" mode.
 * \param dic is the dictionnray the is used to associate characters to their code.
 */
void EncodeFileAVLTree(char* pathOfFileToCompress, BinaryFile* compressedFile, NodeAVLDictionnary* dic);

/**
 * \brief Function to write the dictionnary in the compress file (must called before EncodeFileAVLTree).
 * \n Example:
 * \code{.c}
 * BinaryFile* compressedFile = OpenBinaryFile("Alice.txt");
 * NodeAVLDictionnary* dictionnary = CreerAVLDictionnaire(array);
 *
 * WriteAVLDictionnary(dictionnary, compressedFile);
 * \endcode
 * \param dictionnary is a pointer to the dictionnary to write to the compress file in ordre to decompress it later.
 */
void WriteAVLDictionnary(NodeAVLDictionnary* dictionnary, BinaryFile* fileWithDic);