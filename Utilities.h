#pragma once

#include <stdio.h>

void PrintErrorMessageFromErrorCodeFromFile(errno_t err);

char* AddStringBeforeExtensionOfFileName(char* fileName, char* stringToAdd);

int GetNumberCharInFile(char* path);