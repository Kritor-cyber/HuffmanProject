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

// Functions used to equilibrate the AVL
int _AVLDepth(NodeAVLDictionnary* tree);
int _AVLBalanceFactor(NodeAVLDictionnary* tree);
void _AVLRightRotation(NodeAVLDictionnary** tree);
void _AVLLeftRotation(NodeAVLDictionnary** tree);
void AVLBalance(NodeAVLDictionnary** tree);


void PrintNodeAVLDictionnary(NodeAVLDictionnary* tree);
void FreeNodeAVLDictionnary(NodeAVLDictionnary* tree);