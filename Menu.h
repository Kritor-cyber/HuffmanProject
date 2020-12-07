#pragma once

/**
 * \file   Menu.h
 * \brief  Header of the library used for human interface.
 *
 * \author Thibault DENIER thibault.denier@efrei.net Alias Kritor-cyber
 * \date   December 2020
*/

/**
 * \brief Function to clean the console.
 * \n Example:
 * \code{.c}
 * CleanScreen();
 * \endcode
 */
void CleanScreen();

/**
 * \brief Function to print the menu with variable number of proposition.
 * \n Example:
 * \code{.c}
 * PrintMenu("Please make your choice:", 2, "1. Continue", "2. Exit");
 * \endcode
 * \param intro the string (NULL terminated byte) used to inform the user of what he have to do.
 * \param nbChoice the number of that the user have.
 * \param ... as many string (NULL terminated byte) as nbChoice indicate.
 */
void PrintMenu(const char* intro, int nbChoice, ...);

/**
 * \brief Function that return the integer enter by the user.
 * \n Example:
 * \code{.c}
 * if (GetUserChoice() == 1)
 * 	printf("You make choice 1");
 * else
 * 	printf("You make another choice");
 * \endcode
 * \return the integer enter by the user.
 */
int GetUserChoice();

/**
 * \brief Function that return the string (NULL terminated byte) enter by the user.
 * \n Example:
 * \code{.c}
 * printf("You entered: %s", GetStringFromUser("What do you want? "));
 * \endcode
 * \param msg is a string (NULL terminated byte) to indicate to user what the program is waiting for.
 * \return the integer enter by the user.
 */
char* GetStringFromUser(const char* msg);

/**
 * \brief Function to start the menu.
 * \n Example:
 * \code{.c}
 * int main()
 * {
 *	StartMenu();
 *	return 0;
 * }
 * \endcode
 */
void StartMenu();

/**
 * \brief Function that realy compress the file and automaticaly create automatically used to compress.
 * \n Example:
 * \code{.c}
 * CompressFile();
 * \endcode
 */
void CompressFile();

static void CleanInputBuffer();

static void Pause();

/**
 * \brief Function that decompress binary file with dictionnary include.
 * \n Example:
 * \code{.c}
 * DecompressFile();
 * \endcode
 */
void DecompressFile();

/**
 * \brief Function that write two new files, one with fake binary and another with real binary.
 * \n Example:
 * \code{.c}
 * ConvertIntoFakeBinary();
 * \endcode
 */
void ConvertIntoFakeBinary();