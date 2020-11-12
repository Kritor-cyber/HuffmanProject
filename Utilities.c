#include "Utilities.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintErrorMessageFromErrorCodeFromFile(errno_t err)
{
	char* buffer = (char*)malloc(sizeof(char) * 1024);
	if (buffer != NULL)
	{
		strerror_s(buffer, 1024, err);
		printf("\n\n%s\n\n", buffer);
		free(buffer);
	}
	else
	{
		printf("can't allocate memory to buffer (error for opening file : %d)\n", err);
	}
}