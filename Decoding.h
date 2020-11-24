#pragma once

#include "Structures/NodeHuffman.h"
#include "Structures/AVLTree.h"

void DecodeFromTree(const char* pathToTheFileToDecode, const char* pathToTheDecodedFile, NodeHuffman* tree);