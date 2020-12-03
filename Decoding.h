#pragma once

/**
 * \file   Decoding.h
 * \brief  Header of the library allowing to decompress an ASCII file.
 *
 * \author Thibault DENIER thibault.denier@efrei.net Alias Kritor-cyber
 * \date   December 2020
*/

#include "Structures/NodeHuffman.h"

/**
 * \deprecated Function to uncompress a fake compressed file (with 0 and 1 characters instead of 0 and 1 bits).
 * \n Example:
 * \code{.c}
 * DecodeFromTree("mycompressed.file", "mydecompress.file", tree);
 * \endcode
 * \param pathToTheFileToDecode is the path (string NULL terminated byte) of the file you want to decompress.
 * \param pathToTheDecodedFile is the path (string NULL terminated byte) of the decompress file.
 * \param tree is an Huffman tree that was used to find character that is equivalent to the code.
 */
void DecodeFromTree(const char* pathToTheFileToDecode, const char* pathToTheDecodedFile, NodeHuffman* tree);

/**
 * \brief Function to uncompress a real compressed file (with 0 and 1 bits).
 * \n Example:
 * \code{.c}
 * DecodeCompressedFileWithIntegratedTree("mycompressed.file", "mydecompress.file");
 * \endcode
 * \param pathToTheFileToDecode is the path (string NULL terminated byte) of the file you want to decompress.
 * \param pathToTheDecodedFile is the path (string NULL terminated byte) of the decompress file.
 */
void DecodeCompressedFileWithIntegratedTree(char* pathToTheFileToDecode, char* pathToTheDecodedFile);