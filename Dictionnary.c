#include "Dictionnary.h"

#include <stdio.h>
#include "Utilities.h"

#define DEBUG 0

int GetMaxCodeSize()
{
	FILE* f = NULL;
	errno_t err = fopen_s(&f, "dico.txt", "r");
	if (err || f == NULL)
	{
		printf("Error while opening dico.txt for read\n");
		PrintErrorMessageFromErrorCodeFromFile(err);
		return 0;
	}
	else
	{
		int max = 0;
		char c = '\0';
		
		int cp = 0;
		while (c != EOF)
		{
			c = fgetc(f);
			if (fseek(f, 3, SEEK_CUR))
			{
				printf("Error while changing the file position indicator to 4 on the right\n");
			}
			cp = 0;
			while ((c = fgetc(f)) != '\n' && c != EOF)
			{
				if (DEBUG) printf("%c", c);
				cp++;
			}
			if (DEBUG) printf("\n");
			if (cp > max)
				max = cp;
		}
		fclose(f);

		return max+1;
	}
}

