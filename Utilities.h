#pragma once

/**
 * \file   Utilities.h
 * \brief  Header of the library allowing to do some basic stuff that could use in a lot of projects.
 *
 * \author Thibault DENIER thibault.denier@efrei.net Alias Kritor-cyber
 * \date   December 2020
*/

#include <stdio.h>

/**
 * \brief Function to print the error code return while trying to open a file.
 * \n Example:
 * \code{.c}
 * FILE* file = NULL;
 * errno_t err = fopen_s(&file, "my.file", "r");
 * 
 * if (err != 0)
 * {
 * 	PrintErrorMessageFromErrorCodeFromFile(err);
 * }
 * else
 * {
 * 	...
 * }
 * \endcode
 * \param err is the error code you get after the opening.
 */
void PrintErrorMessageFromErrorCodeFromFile(errno_t err);

/**
 * \brief Function to add a string at the end of another string, but before the extension name (or at the end if no extension), note that the new string and the old string are not free by this function.
 * \n Example:
 * \code{.c}
 * char* newString = AddStringBeforeExtensionOfFileName(oldString, stringToAdd);
 * \endcode
 * \param fileName is the name of the file you want to add a new string at the end (NULL terminated byte).
 * \param stringToAdd is the string you want to add at the end of your file name (NULL terminated byte).
 * \return a pointer to the new string.
 * \return \c NULL if an error occured during the process.
 */
char* AddStringBeforeExtensionOfFileName(char* fileName, char* stringToAdd);

/**
 * \brief Function that return the number of char composing a file.
 * \n Example:
 * \code{.c}
 * int number = GetNumberCharInFile("my.file");
 * \endcode
 * \param path is a string that represent the local or global path to the file (NULL terminated byte).
 * \return the number of character.
 * \return -1 if the file can't be opened and print a message on the console.
 */
int GetNumberCharInFile(char* path);

/**
 * \brief Function that write a string (NULL terminated byte) in "fake" binary at the end of a file.
 * \n Example:
 * \code{.c}
 * WriteInBinary(myFile, "my string to convert");
 * \endcode
 * \param file is the file you want to write in.
 * \param string is the text you want to convert and write.
 */
void WriteInBinary(FILE* file, char* string);