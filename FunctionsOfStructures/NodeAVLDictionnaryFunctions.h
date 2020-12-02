#pragma once

#include "../Structures/NodeAVLDictionnary.h"

// Functions used to equilibrate the AVL
static int _AVLDepth(NodeAVLDictionnary* tree);
static int _AVLBalanceFactor(NodeAVLDictionnary* tree);
static void _AVLRightRotation(NodeAVLDictionnary** tree);
static void _AVLLeftRotation(NodeAVLDictionnary** tree);
void AVLBalance(NodeAVLDictionnary** tree);

void PrintNodeAVLDictionnary(NodeAVLDictionnary* tree);
void FreeNodeAVLDictionnary(NodeAVLDictionnary* tree);