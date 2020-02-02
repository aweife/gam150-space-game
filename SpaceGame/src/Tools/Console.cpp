/*********************************************************************************
* \file			Editor.cpp
* \author		Chong Jun Yi
* \version		1.0
* \date			18/01/2019
* \par			Engine Code
* \note			Course: GAM150
* \brief		Abstraction for console window
				- print custom outputs with debug logger
				- check AE_Assert statements
				-

* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "AEEngine.h"   //Time
#include "Console.h"		
#include <Windows.h>	//Most console api - HANDLE, 
#include <iostream>		//cout Text
#include "../Global.h"  

static HANDLE sConsoleOutHandle = 0x00;			//Handle for console screen
COORD sConsoleSize;								//The size of console screen

/******************************************************************************/
/*!
  \brief	Initalise Console Window
*/
/******************************************************************************/
void Console_Init()
{
	// Main buffer in normal mode, Backbuffer in double buffering
	sConsoleOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//HANDLE sConsoleInHandle = GetStdHandle(STD_INPUT_HANDLE);

//------------------------------------------------------------
//	CONSOLE FONT SETTINGS
//------------------------------------------------------------
	
	// Get Font information
	//CONSOLE_FONT_INFO origfontInfo;
	//GetCurrentConsoleFont(sConsoleOutHandle, FALSE, &origfontInfo);
	//printf("Font size %d %d\n", origfontInfo.dwFontSize.X, origfontInfo.dwFontSize.Y);

	// Create new console font data
	//CONSOLE_FONT_INFOEX fontInfo = { 0 };
	//fontInfo.cbSize = sizeof(fontInfo);	//set struct size

	// Change Font type - copy the name of the typeface - (Default : Raster font, (7, 16))
	//wcscpy_s(fontInfo.FaceName, _countof(fontInfo.FaceName), L"Terminal"); 
	
	//fontInfo.dwFontSize.X = 7;
	//fontInfo.dwFontSize.Y = 16;
	//fontInfo.FontWeight = FW_NORMAL;


	// Update to new font
	//SetCurrentConsoleFontEx(sConsoleOutHandle, FALSE, &fontInfo);

//------------------------------------------------------------
//	CONSOLE WINDOW SETTINGS (Size -> Position -> Layer)
//------------------------------------------------------------

	// Set the console size
	Console_SetSize(150, 40); //Load Screen buffer based on size

	// Set the console at top left corner
	Console_SetWindowPos(0, 60);
	// Place the console on top of game window
	//BringWindowToTop(GetConsoleWindow());
}

/******************************************************************************/
/*!
  \brief	Move the console window to coord (x, y)
*/
/******************************************************************************/
void Console_SetWindowPos(int x, int y)
{
	SetWindowPos(GetConsoleWindow(), HWND_TOP, x, y, 0, 0, SWP_FRAMECHANGED | SWP_DRAWFRAME | SWP_NOSIZE);
}

/******************************************************************************/
/*!
  \brief	Resize the console to user specifed size
  \note		If monitor size has contraint, resize to maximum possible size
*/
/******************************************************************************/
void Console_SetSize(short x, short y)
{
	// Check if user defined size exceed laptop screen
	const COORD maxSize = GetLargestConsoleWindowSize(sConsoleOutHandle);
	short yOffset = 2;
	x = x <= maxSize.X ? x : maxSize.X;
	y = y <= maxSize.Y - yOffset ? y : maxSize.Y - yOffset;

	const COORD consoleSize = {x, y};
	const COORD screenBufferSize = { x, 9001};										//Define Screen Buffer Size
	const SMALL_RECT windowSize = { 0, 0, consoleSize.X - 1, consoleSize.Y - 1 };	//Define Console Window Size
	const SMALL_RECT smallWindowSize = { 0, 0, 1, 1 };
	
	/* HACK: sometimes the windows is not of the asked size, because the Buffer can never be smaller than the windows*/
	/* FIX: Force a small windows, set buffer, and resize windows to the correct size*/
	SetConsoleWindowInfo(sConsoleOutHandle, 1, &smallWindowSize);
	SetConsoleScreenBufferSize(sConsoleOutHandle, screenBufferSize);
	SetConsoleWindowInfo(sConsoleOutHandle, 1, &windowSize);

	sConsoleSize = consoleSize;	//Update the current console size
}

/******************************************************************************/
/*!
  \brief	Display text using Cout functions
*/
/******************************************************************************/
void Console_Cout(short x, short y, const char* s)
{
	Console_SetCursorPos(x, y);
	std::cout << s << std::endl;
}

void Console_Cout(const char* s)
{
	std::cout << s << std::endl;
}

void Console_Cout(const std::string s)
{
	std::cout << s << std::endl;
}

void Console_Cout(const char* s, int num)
{
	std::cout << s << " " << num << std::endl;
}

void Console_Cout(const std::string s, int num)
{
	std::cout << s << " " << num << std::endl;
}


/******************************************************************************/
/*!
  \brief	Display detail information
  \note		Sample: Console_CoutDetailed("HELLO WORLD", __LINE__, __FUNCTION__);
            Console_CoutDetailed("HELLO WORLD", 123 ,__LINE__, __FUNCTION__, __FILE__);
			file and number is a default parameter
*/
/******************************************************************************/
void Console_CoutDetailed(const char* s, const int line, const char* function, const char* file, int number)
{
	f64 time = AEGetTime(&time) - gStartTime;

	std::cout << "-------------------------------" << std::endl;
	std::cout << "Line: " << line << " Function: " << function << " File: "<< file << " Time: " << time << std::endl;
	std::cout << s << " "<< number << std::endl;
	std::cout << "-------------------------------" << std::endl;
}

/******************************************************************************/
/*!
  \brief	Cout Newline
*/
/******************************************************************************/
void Console_Newline(int repeat)
{
	while (repeat > 0) {
		std::cout << std::endl;
		--repeat;
	}
}

/******************************************************************************/
/*!
  \brief	Get the coordinate of console cursor
*/
/******************************************************************************/
COORD Console_GetCursorPos()
{
	CONSOLE_SCREEN_BUFFER_INFO  screenBufferInfo;
	GetConsoleScreenBufferInfo(sConsoleOutHandle, &screenBufferInfo);	//Get sConsole Screen Buffer

	return screenBufferInfo.dwCursorPosition;	//Return the current cursor location
}

/******************************************************************************/
/*!
  \brief	Set the coordinate of console cursor
*/
/******************************************************************************/
void Console_SetCursorPos(short x, short y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(sConsoleOutHandle, pos);
}

/******************************************************************************/
/*!
  \brief	Set the coordinate of console cursor
*/
/******************************************************************************/
void Console_SetCursorPos(COORD c)
{
	SetConsoleCursorPosition(sConsoleOutHandle, c);
}


/******************************************************************************/
/*!
  \brief	Clear a square area in the console window
			Will not overflow to next line if exceed width
*/
/******************************************************************************/
void Console_ClearArea(short topX, short topY, short width, short height)
{
	COORD topLeft = {topX, topY};	//Starting coordinate to Clear
	COORD oldPos;					//Console Cursor
	DWORD writtenCells;
	short clearWidth = width + topX >= sConsoleSize.X? sConsoleSize.X - topX: width;

	oldPos = Console_GetCursorPos();		//Get the current cursor location

	for (short i = 0; i < height; ++i)
	{
		++topLeft.Y;
		FillConsoleOutputCharacterA(sConsoleOutHandle, ' ', clearWidth, topLeft, &writtenCells);	//Fill char ANSI style
		FillConsoleOutputAttribute(sConsoleOutHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			clearWidth, topLeft, &writtenCells);
	}
	Console_SetCursorPos(oldPos);				//Restore current cursor location
}
/******************************************************************************/
/*!
  \brief	Clear the entire console window
*/
/******************************************************************************/
void Console_ClearAll()
{
	
	CONSOLE_SCREEN_BUFFER_INFO screenInfoBuffer;
	GetConsoleScreenBufferInfo(sConsoleOutHandle, &screenInfoBuffer);
	const int cellCount = screenInfoBuffer.dwSize.X * screenInfoBuffer.dwSize.Y; /*Count of all the cells in the window*/
	const COORD firstCell = { 0, 0 };
	DWORD writtenCells = 0;

	/* Fills the whole console with a space character*/
	FillConsoleOutputCharacterA(sConsoleOutHandle, ' ', cellCount, firstCell, &writtenCells);/*Fill all the memory with ' '*/
	//Clean out properly the colors if you decide to use colors
	FillConsoleOutputAttribute(sConsoleOutHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		cellCount, firstCell, &writtenCells);
}

/******************************************************************************/
/*!
  \brief	Clean up when exit executable
*/
/******************************************************************************/
void Console_CleanUp()
{
	//Console_FreeRenderBuffer();
	Console_ClearAll();
	DestroyWindow(GetConsoleWindow());
}