#include <stdio.h>
#include <stdlib.h>

#include "StringManipulation.h"
#include "FileManipulation.h"

int main(int argc, char* argv[])
{
	printf("Compression de fichiers textes...\n\n");
	if (argc != 2 && argc != 3)
	{
		printf("usage Huffman.exe \"file to compress.txt\"\nor\n");
		printf("usage Huffman.exe \"file to compress.txt\" \"name of the compressed file.txt\"\n");
		return 0;
	}


	printf("Gonna convert \"Alice.txt\" into binary...\n");

	ConvertFileFromASCIIToBinary(argv[1]);
	printf("\"Alice.txt\" into binary convertion finished...\n");

	char* binaryFile = AddStringBeforeExtensionOfFileName(argv[1], "_binary");
	int nbCharInFile = GetNumberCharInFile(argv[1]);
	if (nbCharInFile == -1)
		printf("There is no character in %s\n", argv[1]);
	else
		printf("There are %d char in %s\n", nbCharInFile, argv[1]);

	nbCharInFile = GetNumberCharInFile(binaryFile);
	if (nbCharInFile == -1)
		printf("There is no character in %s\n", binaryFile);
	else
		printf("There are %d char in %s\n", GetNumberCharInFile(binaryFile), binaryFile);
	
	free(binaryFile);

	return 0;
}