#pragma once

void PrintMenu(const char* intro, int nbChoice, ...);

int GetUserChoice();

char* GetStringFromUser(const char* msg);

void StartMenu();

void CompressFile();

static void CleanInputBuffer();

static void Pause();

void CompressFile();

void DecompressFile();

void ConvertIntoFakeBinary();