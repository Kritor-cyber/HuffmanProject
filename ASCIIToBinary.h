#pragma once
/**
 * \file   ASCIIToBinary.h
 * \brief  Header of the library allowing to convert characters into their binary version.
 *
 * \author Samy AIT-SSI samy.ait.ssi@efrei.net Alias Kapinorhm
 * \date   December 2020
*/

/**
* \brief Function writing in string the binary version of the ASCII characters and shows error message if no memory was allocated to contain the binary version.
* \n Example :
* \code{.c}
* char bitsComposing[9];
* bitsComposing[8] = '\0';
* CharacterToBinary(bitsComposing, 'a');
* printf("%s", bitsComposing);
* \endcode
* \param bitsComposingChar is an allocated memory affecting the binary version of a character.
* \param charToConvert is the character the function converts into its binary version.
*/
void CharacterToBinary(char* bitsComposingChar, char charToConvert);

/**
* \brief Function writing the binary version of a characters file.
* \n Example :
* \code{.c}
* ConvertFileFromASCIIToBinary("Alice.txt");
* \endcode
* \param path is the path to the file to convert from characters into binary.
*/
void ConvertFileFromASCIIToBinary(char* path);

