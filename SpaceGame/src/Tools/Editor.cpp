/**********************************************************************************
* \file			Editor.cpp
* \brief		Low level editor using console to modify game variables
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "AEEngine.h"				//AESysGetWindowHandle
#include <Windows.h>				//RECT
#include <unordered_map>			//Variable Tracker
#include "Editor.h"					//Self Header
#include "Console.h"				//Cout Text

//A list of variables to constantly print at the same position in the console window
std::unordered_map<const char*, float> variableList;			

/******************************************************************************/
/*!
  \brief	Initalise Editor, move the windows to a comfortable debug _position
*/
/******************************************************************************/
void Editor_Init()
{
	HWND gameWindow = AESysGetWindowHandle();
	//Reposition the game window to see console window
	RECT   applicationRect;
	RECT   desktopRect;
	GetWindowRect(gameWindow, &applicationRect);
	GetWindowRect(GetDesktopWindow(), &desktopRect);

	//Reposition game window to top right corner
	int xnew = desktopRect.right - (applicationRect.right - applicationRect.left);
	int ynew = 0;// 60;//desktopRect.bottom - (applicationRect.bottom - applicationRect.top);	//Offset to see visual studio taskbar
	SetWindowPos(gameWindow, HWND_NOTOPMOST, xnew, ynew, 0, 0, SWP_FRAMECHANGED | SWP_DRAWFRAME | SWP_NOSIZE);
	
}

/******************************************************************************/
/*!
  \brief	Logic and data manipulation
*/
/******************************************************************************/
void Editor_Update()
{
	variableList.clear();						//Clear variable Tracking List before GameStateUpdate
}

/******************************************************************************/
/*!
  \brief	Render text onto the console based on concepts of xtext buffer
*/
/******************************************************************************/
void Editor_Render()
{
	COORD originMouse = Console_GetCursorPos();			//Get the mouse position before jumping around Console
	COORD consoleSize = Console_GetConsoleSize();
	short verticalOffset = originMouse.Y  > consoleSize.Y ? originMouse.Y - consoleSize.Y : 0;

	//Tracking Variables
	Console_ClearArea(0, verticalOffset, 100, static_cast<short>(variableList.size() + 3));
	Console_Cout(0, verticalOffset + 2, "Tracking Variables");
	for (auto &i :variableList)
	{
		Console_Cout(i.first, i.second);
	}

	Console_SetCursorPos(originMouse.X, originMouse.Y);
}

/******************************************************************************/
/*!
  \brief	Print and refresh a certain spot to constantly track a int/float variable
*/
/******************************************************************************/
void Editor_TrackVariable(const char* text, float value)
{
	//Check if variables is new
	if (variableList.find(text) == variableList.end())
	{
		variableList.insert({text , value});
	}
}

void Editor_TrackVariable(const char* text, int value)
{
	Editor_TrackVariable(text, static_cast<float>(value));
}


/******************************************************************************/
/*!
  \brief	Resize the game window to user specifed size
  \note		If monitor size has contraint, resize to maximum possible size
*/
/******************************************************************************/
void Editor_SetSize(short x, short y)
{
	// Check if user defined size exceed laptop screen
	RECT   desktopRect;
	GetWindowRect(GetDesktopWindow(), &desktopRect);
	const COORD maxSize = { static_cast<short>(desktopRect.right - desktopRect.left),  static_cast<short>(desktopRect.bottom - desktopRect.top)};
	short yOffset = 2;
	x = (x <= maxSize.X) ? x : maxSize.X;
	y = (y <= maxSize.Y - yOffset) ? y : maxSize.Y - yOffset;

	HWND gameWindow = AESysGetWindowHandle();
	SetWindowPos(gameWindow, HWND_NOTOPMOST, 0, 0, x, y, SWP_FRAMECHANGED | SWP_DRAWFRAME );
}
