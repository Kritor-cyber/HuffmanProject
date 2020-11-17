#pragma once

#include <stdio.h>

void GetCharCodeFromDic(FILE* dic, char c, char* code);
void EncodeFile(char* pathOfFileToCompress, char* pathOfFileCompressed, FILE* dic);