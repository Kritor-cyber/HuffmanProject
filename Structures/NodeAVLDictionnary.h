#pragma once

#include "NodeHuffman.h"

typedef struct NodeAVLDictionnary
{
	char c;
	char* code;
	struct NodeAVLDictionnary* left;
	struct NodeAVLDictionnary* right;
} NodeAVLDictionnary;

void AddNodeInNodeDictionnary(NodeAVLDictionnary** dic, char c, char* code);
NodeAVLDictionnary* CreerAVLDictionnaire(NodeHuffman* tree);
void _CreerAVLDictionnaire(NodeHuffman* actualNode, char* code, int codeSize, NodeAVLDictionnary** tree);

char* GetCharCodeFromAVLDic(NodeAVLDictionnary* dic, char c);