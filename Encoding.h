#pragma once

#include "Structures/NodeAVLDictionnary.h"

#include <stdio.h>
#include "Structures/BinaryFile.h"

void GetCharCodeFromDic(FILE* dic, char c, char* code);
void EncodeFile(char* pathOfFileToCompress, char* pathOfFileCompressed, FILE* dic);

void EncodeFileAVLTree(char* pathOfFileToCompress, BinaryFile* compressedFile, NodeAVLDictionnary* dic);
void WriteAVLDictionnary(NodeAVLDictionnary* tree, BinaryFile* fileWithDic);