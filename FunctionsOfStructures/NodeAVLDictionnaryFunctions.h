#pragma once

#include "../Structures/NodeAVLDictionnary.h"

// Functions used to equilibrate the AVL
int _AVLDepth(NodeAVLDictionnary* tree);
int _AVLBalanceFactor(NodeAVLDictionnary* tree);
void _AVLRightRotation(NodeAVLDictionnary** tree);
void _AVLLeftRotation(NodeAVLDictionnary** tree);
void AVLBalance(NodeAVLDictionnary** tree);

void PrintNodeAVLDictionnary(NodeAVLDictionnary* tree);
void FreeNodeAVLDictionnary(NodeAVLDictionnary* tree);