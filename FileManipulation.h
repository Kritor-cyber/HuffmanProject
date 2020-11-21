#pragma once

#include "Structures/ListCharAndNbOcc.h"

void ConvertFileFromASCIIToBinary(char* path);
int GetNumberCharInFile(char* path);
ListCharAndNbOcc* GetListCharAndNbOccFromFile(char* path);