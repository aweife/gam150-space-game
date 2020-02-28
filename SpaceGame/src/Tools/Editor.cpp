/*********************************************************************************
* \file			Editor.cpp
* \author		Chong Jun Yi
* \version		1.0
* \date			18/01/2019
* \par			Engine Code
* \note			Course: GAM150
* \brief		Low level editor using console to modify game variables
				- 
				- 

* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "AEEngine.h"				//AESysGetWindowHandle
#include <Windows.h>				//RECT
#include <unordered_map>			//Variable Tracker
#include "Editor.h"					//Self Header
#include "Console.h"


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
	int ynew = 60;//desktopRect.bottom - (applicationRect.bottom - applicationRect.top);	//Offset to see visual studio taskbar
	SetWindowPos(gameWindow, HWND_NOTOPMOST, xnew, ynew, 0, 0, SWP_FRAMECHANGED | SWP_DRAWFRAME | SWP_NOSIZE);
	
}

void Editor_Update()
{
	variableList.clear();						//Clear variable Tracking List before GameStateUpdate
}

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