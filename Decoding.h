#pragma once

#include "Structures/NodeHuffman.h"

void DecodeFromTree(const char* pathToTheFileToDecode, const char* pathToTheDecodedFile, NodeHuffman* tree);