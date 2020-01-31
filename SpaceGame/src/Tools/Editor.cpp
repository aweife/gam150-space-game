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
#include "AEEngine.h"
#include "Editor.h"
#include <Windows.h>
#include "Console.h"
#include <iostream>
//Console variables



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
	int ynew = -0;//desktopRect.bottom - (applicationRect.bottom - applicationRect.top);
	SetWindowPos(gameWindow, HWND_NOTOPMOST, xnew, ynew, 0, 0, SWP_FRAMECHANGED | SWP_DRAWFRAME | SWP_NOSIZE);
	
}

void Editor_Update()
{

}

