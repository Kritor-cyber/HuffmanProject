#pragma once

#include "Structures/NodeAVLDictionnary.h"

#include <stdio.h>

void GetCharCodeFromDic(FILE* dic, char c, char* code);
void EncodeFile(char* pathOfFileToCompress, char* pathOfFileCompressed, FILE* dic);

void EncodeFileAVLTree(char* pathOfFileToCompress, char* pathOfFileCompressed, NodeAVLDictionnary* dic);
void WriteAVLDictionnary(NodeAVLDictionnary* tree, FILE* dic);