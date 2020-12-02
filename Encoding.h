#pragma once

#include "Structures/NodeAVLDictionnary.h"

#include <stdio.h>
#include "Structures/BinaryFile.h"

void EncodeFileAVLTree(char* pathOfFileToCompress, BinaryFile* compressedFile, NodeAVLDictionnary* dic);
void WriteAVLDictionnary(NodeAVLDictionnary* tree, BinaryFile* fileWithDic);