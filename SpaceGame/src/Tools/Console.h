/**********************************************************************************
* \file			Console.h
* \brief		Abstraction for console window
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*				Long Description
*				- print custom outputs with debug logger
*				- Text Alignment
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H
#include <windows.h>//COORD
#include <string>

void Console_Init();

void Console_SetWindowPos(int x, int y);

void Console_SetSize(short x, short y);

void Console_Cout(short x, short y, const char* s);
void Console_Cout(const char* s);
void Console_Cout(const std::string s);
void Console_Cout(const char* s, int num);
void Console_Cout(const char* s, float num);
void Console_Cout(const std::string s, int num);
void Console_CoutDetailed(const char* s, const int line, const char* function, const char* file = " ", int number = 0);

void Console_Newline(int repeat = 1);

COORD Console_GetCursorPos();
void Console_SetCursorPos(short x, short y);
void Console_SetCursorPos(COORD c);

COORD Console_GetConsoleSize();

void Console_ClearArea(short topX, short topY, short width, short height);
void Console_ClearAll();

void Console_CleanUp();

#endif