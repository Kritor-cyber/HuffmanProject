#pragma once

#include "Structures/NodeHuffman.h"

void DecodeFromTree(const char* pathToTheFileToDecode, const char* pathToTheDecodedFile, NodeHuffman* tree);

void DecodeCompressedFileWithIntegratedTree(char* pathToTheFileToDecode, char* pathToTheDecodedFile);