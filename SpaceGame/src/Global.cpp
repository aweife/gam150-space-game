/*********************************************************************************
* \file			Global.cpp
* \author		Ang Wei Feng, Chong Jin Kiat, Chong Jun Yi, Farzaana Binte Roslan
* \version		1.0
* \date			18/01/2020
* \par			Data storage Code
* \note			Course: GAM150
* \brief		Stores global variables about the game
				- Game Start Time (Time when exe was lauched)
				-

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "Global.h"
#include "Tools/Console.h"
#include "AEEngine.h"			//Time
#include "Systems/DebugToolsSystem.h"		//Generate bounding box outline

bool		g_DebugEditor	= false;					// Should the game show a console window
bool		g_GamePause		= false;					// Is the game paused?
bool		g_BBShowMode  = false;					// Display all outline of mesh rigidbody

//Time Based
float		g_dt			= 0.0f;						// Delta Time for game
float		g_appTime		= 0.0f;						// Time since game was started		

//Window Based
float		g_WorldMinX		= 0.0f;						// World(Game) screen minimum X coordinates
float		g_WorldMaxX		= 0.0f;						// World(Game) screen maximum X coordinates
float		g_WorldMinY		= 0.0f;						// World(Game) screen minimum Y coordinates
float		g_WorldMaxY		= 0.0f;						// World(Game) screen maximum Y coordinates

RECT		g_WindowRect;								// Size of windowRect in pixels 
long		g_WindowWidth;								// window Width
long		g_WindowHeight;								// window Height

AEVec2 defaultAEVec2 = { 0,0 };
float defaultFloat = 0.0f;

/******************************************************************************/
/*!
  \brief	Get data when game starts
*/
/******************************************************************************/
void Global_Init()
{
	g_WorldMinX = AEGfxGetWinMinX(); // World minimum X coordinates
	g_WorldMinY = AEGfxGetWinMinY(); // World minimum Y coordinates 
	g_WorldMaxX = AEGfxGetWinMaxX(); // World maximum X coordinates
	g_WorldMaxY = AEGfxGetWinMaxY(); // World maximum Y coordinates

	GetWindowRect(AESysGetWindowHandle(), &g_WindowRect);		// Get Size of the windows display
	g_WindowWidth = g_WindowRect.right - g_WindowRect.left;		// Calculate window Width
	g_WindowHeight = g_WindowRect.bottom - g_WindowRect.top;	// Calculate window Height...-30 for the title
}

/******************************************************************************/
/*!
  \brief	Pause or unpause the game
*/
/******************************************************************************/
void TogglePause()
{
	if (g_GamePause)
	{
		Console_CoutDetailed("Game is Unpaused", -1, " ");
	}
	else
	{
		Console_CoutDetailed("Game is Paused", -1, " ");
	}
	g_GamePause = !g_GamePause;
}

void ToggleShowBoundingBoxMode()
{
	if (g_BBShowMode)
	{
		RemoveAll_BoundingBoxOutline();
	}
	else
	{
		ShowAll_BoundingBoxOutline();
	}
	g_BBShowMode = !g_BBShowMode;
}

