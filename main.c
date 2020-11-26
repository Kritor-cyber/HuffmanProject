#include <stdio.h>
#include <stdlib.h>

#include "ASCIIToBinary.h"
#include "Utilities.h"
#include "Structures/ListCharAndNbOcc.h"
#include "Structures/NodeHuffman.h"
#include "Encoding.h"
#include "Decoding.h"
#include "Dictionnary.h"
#include "Structures/NodeAVLDictionnary.h"

#define DEBUG 1

int main(int argc, char* argv[])
{
	printf("Compression de fichiers textes...\n\n");
	if (argc != 2 && argc != 3)
	{
		printf("usage Huffman.exe \"file to compress.txt\"\nor\n");
		printf("usage Huffman.exe \"file to compress.txt\" \"name of the compressed file.txt\"\n");
		return 0;
	}


	printf("Gonna convert \"%s\" into binary...\n", argv[1]);

	ConvertFileFromASCIIToBinary(argv[1]);
	printf("\"%s\" into binary convertion finished...\n", argv[1]);

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

	ListCharAndNbOcc* list = GetListCharAndNbOccFromFile(argv[1]);

	if (list == NULL)
	{
		printf("file is empty or an eeror occurred\n");
	}
	else
	{
		if (DEBUG)
		{
			PrintList(list);
			NodeHuffman* huffmanTree = CreateHuffmanTree(list);
			PrintList(list);
			PrintHuffmanTree(huffmanTree);
			WriteDictionnary(huffmanTree);

			
			FILE* dic = NULL;
			errno_t err = fopen_s(&dic, "dico.txt", "r");

			if (err || dic == NULL)
			{
				printf("There is an error while opening the dictionnary\n");
			}
			else
			{
				char* pathOfFileCompressed = AddStringBeforeExtensionOfFileName(argv[1], "_compressed");
				if (pathOfFileCompressed == NULL)
				{
					printf("Error while allocating memory to pathOfFileCompressed\n");
				}
				else
				{
					printf("Encoding %s\n", argv[1]);
					EncodeFile(argv[1], pathOfFileCompressed, dic);
					printf("Encoding finished\n");

					char* pathOfFileDecompressed = AddStringBeforeExtensionOfFileName(argv[1], "_decompressed");
					if (pathOfFileDecompressed == NULL)
					{
						printf("Error while allocating memory to pathOfFileCompressed\n");
					}
					else
					{
						printf("Decoding %s\n", pathOfFileCompressed);
						DecodeFromTree(pathOfFileCompressed, pathOfFileDecompressed, huffmanTree);
						printf("Decoding finished\n");
						
						printf("Creating array with all leaves of huffman tree\n");
						FILE* fTmp;
						err = fopen_s(&fTmp, pathOfFileDecompressed, "r");
						if (err || fTmp == NULL)
						{
							printf("There is an error while opening the file decompressed\n");
						}
						else
						{
							NodeHuffman** tabTmp = NULL;
							int sizeTab;
							printf("Dichotomy version\n");
							tabTmp = _CreateArrayOfNodeHuffmanWithNbOccFromFile(fTmp, &sizeTab);
							if (tabTmp != NULL)
							{
								for (int i = 0; i < sizeTab; i++)
								{
									if (tabTmp[i] != NULL)
									{
										printf("%c : %d\n", tabTmp[i]->c, tabTmp[i]->nbOcc);
										free(tabTmp[i]); // We do this because we are erasing all the data in the array in the next step
									}
									else
									{
										printf("tabTmp[%d] is NULL pointer, and this should not happend\n", i);
									}
								}
							}

							fseek(fTmp, 0, SEEK_SET);
							printf("\n\nOur version without dichotomy\n");
							tabTmp = _CreateArrayOfNodeHuffmanWithNbOccFromFile(fTmp, &sizeTab);
							if (tabTmp != NULL)
							{
								for (int i = 0; i < sizeTab; i++)
								{
									printf("%c : %d\n", tabTmp[i]->c, tabTmp[i]->nbOcc);
								}
								SortArrayByNbOcc(tabTmp, sizeTab);	// WARNING : The array need to be short for CreateHuffmanTreeFromArray() function
								for (int i = 0; i < sizeTab; i++)
								{
									printf("%c : %d\n", tabTmp[i]->c, tabTmp[i]->nbOcc);
								}

								NodeHuffman* huffTree = CreateHuffmanTreeFromArray(tabTmp, sizeTab);
								PrintHuffmanTree(huffmanTree);
								printf("\n\n");
								PrintHuffmanTree(huffTree);
								printf("\n");

								NodeAVLDictionnary* dictionnary = CreerAVLDictionnaire(huffTree);
								PrintNodeAVLDictionnary(dictionnary);
								
								char* pathOfFileCompressed2 = AddStringBeforeExtensionOfFileName(pathOfFileCompressed, "_opti");
								if (pathOfFileCompressed2 == NULL)
								{
									printf("Error while allocating memory to pathOfFileCompressed2\n");
								}
								else
								{
									printf("Encoding %s\n", argv[1]);
									EncodeFileAVLTree(argv[1], pathOfFileCompressed2, dictionnary);
									printf("Encoding finished\n");
									free(pathOfFileCompressed2);
								}
								
								FILE* newDicFile;
								err = fopen_s(&newDicFile, "newDico.txt", "w");
								if (err || newDicFile == NULL)
								{
									printf("There is an error while opening the file decompressed\n");
								}
								else
								{
									printf("\nWriting dictionnary...\n");
									WriteAVLDictionnary(dictionnary, newDicFile);
									printf("Dictionnary writing finished...\n");
									fclose(newDicFile);
								}


								err = fopen_s(&newDicFile, "newDico.txt", "r");
								if (err || newDicFile == NULL)
								{
									printf("There is an error while opening the file decompressed\n");
								}
								else
								{
									if (dictionnary != NULL)
									{
										char* pathOfFileCompressed3 = AddStringBeforeExtensionOfFileName(pathOfFileCompressed, "_withChargedDic");
										if (pathOfFileCompressed3 == NULL)
										{
											printf("Error while allocating memory to pathOfFileCompressed3\n");
										}
										else
										{
											printf("Encoding %s\n", argv[1]);
											EncodeFileAVLTree(argv[1], pathOfFileCompressed3, dictionnary);
											printf("Encoding finished\n");

											NodeHuffman* treeToDecompress = CreateHuffmanTreeFromDictionnaryFile("dico.txt");
											char* pathOfFileDecompressed2 = AddStringBeforeExtensionOfFileName(pathOfFileDecompressed, "_fromDicFile");
											if (treeToDecompress != NULL && pathOfFileDecompressed2 != NULL)
											{
												printf("Decoding %s\n", pathOfFileCompressed3);
												DecodeFromTree(pathOfFileCompressed, pathOfFileDecompressed2, huffmanTree);
												printf("Decoding finished\n");
												free(pathOfFileDecompressed2);
											}

											free(pathOfFileCompressed3);
										}

										FreeNodeAVLDictionnary(dictionnary);
									}
								}
								FreeHuffmanTree(huffTree);
								// The tree as already been free so all datas in the array are free, no need to refree them
								free(tabTmp);
								fclose(fTmp);
							}
						}
						free(pathOfFileDecompressed);
					}

					free(pathOfFileCompressed);
				}
			}

			FreeList(list);
			list = NULL;
			FreeHuffmanTree(huffmanTree);
			huffmanTree = NULL;
		}
	}

	return 0;
}