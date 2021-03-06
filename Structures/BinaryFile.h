	#pragma once
/**
 * \file   BinaryFile.h
 * \brief  Header of the library dedicated to open or close, convert and write, get and read binary files.
 *
 * \author Samy AIT-SSI samy.ait.ssi@efrei.net Alias Kapinorhm
 * \date   December 2020
*/

#include <stdio.h>

/**
* \typedef struct BinaryFile
* \brief structur of the binary file, with a buffer and a sizeBuffer.
*/
typedef struct BinaryFile
{
	FILE* file;
	char buffer;
	char sizeBuffer;
} BinaryFile;

/**
* \brief Function opening a binary file.
* \n Example :
* \code{.c}
* OpenBinaryFile(path, "rb");
* \endcode
* \param path is the path to the binary file.
* \param mode is the mode of opening the binary file.
* \return the binary file.
* \return an error message if path to file can't be opened.	
*/
BinaryFile* OpenBinaryFile(char* path, char* mode);

/**
* \brief Function that converts and writes a character's binary form in a file.
* \n Example :
* \code{.c}
* WriteCharIntoBinaryFile(file,'a');
* \endcode
* \param file is the file where the binary version of the character will be written.
* \param charToWrite is the parameter converted into a binary version.
*/
void WriteCharIntoBinaryFile(BinaryFile* file, char charToWrite);

/**
* \brief Function that writes "fake" bits in a binary file.
* \n Example :
* \code{.c}
* WriteFakeBitsIntoBinaryFile(file, bitsCode);
* \endcode
* \param file is the file where the bits will be written.
* \param bitsCode are the numerous bits which will be written in the file.
*/
void WriteFakeBitsIntoBinaryFile(BinaryFile* file, char* bitsCode);

/**
* \brief Function that writes a "fake" bit in a binary file.
* \n Example :
* \code{.c}
* WriteFakeBitIntoBinaryFile(file, bit);
* \endcode
* \param file is the file where the "fake" bit will be written.
* \param fakeBit is the "fake" bit that will be written in the file.
*/
void WriteFakeBitIntoBinaryFile(BinaryFile* file, char fakeBit);

/**
* \brief Function that Force-writes a "fake" bit in a binary file.
* \n Example :
* \code{.c}
* ForceWriteBits(file);
* \endcode
* \param file is the file where the "fake" bit will be force-written.
*/
void ForceWriteBits(BinaryFile* file);

/**
* \brief Function that gets a character from the binary file.
* \n Example :
* \code{.c}
* GetCharFromBinaryFile(file);
* \endcode
* \param file is the file the character will get pulled from.
* \return the character read bit per bit.
*/
char GetCharFromBinaryFile(BinaryFile* file);

/**
* \brief Function that gets a bit from the binary file.
* \n Example :
* \code{.c}
* GetFakeBitFromBinaryFile(file)
* \endcode
* \param file is the file the bit will get pulled from.
* \return the last bit read.
*/
char GetFakeBitFromBinaryFile(BinaryFile* file);

/**
* \brief Function that closes a file.
* \n Example :
* \code{.c}
* CloseBinaryFile(file);
* \endcode
* \param fileToClose is the file to close and deallocate the memory from.
*/
void CloseBinaryFile(BinaryFile* fileToClose);