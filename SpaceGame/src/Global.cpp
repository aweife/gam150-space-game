/**********************************************************************************
* \file			Global.cpp
* \brief		Stores global variables about gameplay, time and window size
* \author		Jun Yi,			Chong,		75% Code Contribution
*				Jin Kiat,		Chong,		25% Code Contribution
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#include "Global.h"										//Variable Declaration
#include "AEEngine.h"									//Time
#include "Systems/DebugToolsSystem.h"					//Generate bounding box outline

//Game State
bool		g_DebugEditor	= false;					// Should the game show a console window
bool		g_GamePause		= false;					// Is the game paused?
bool		g_BBShowMode  = false;						// Display all outline of mesh rigidbody

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

//Default values for references
AEVec2 defaultAEVec2 = { 0,0 };
float defaultFloat = 0.0f;

/******************************************************************************/
/*!
  \brief	Get data when game starts
*/
/******************************************************************************/
void Global_Init()
{
	g_WorldMinX = AEGfxGetWinMinX();					// World minimum X coordinates
	g_WorldMinY = AEGfxGetWinMinY();					// World minimum Y coordinates 
	g_WorldMaxX = AEGfxGetWinMaxX();					// World maximum X coordinates
	g_WorldMaxY = AEGfxGetWinMaxY();					// World maximum Y coordinates

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
	g_GamePause = !g_GamePause;
}

/******************************************************************************/
/*!
  \brief	Show any debug mesh outline or vector visualisation
*/
/******************************************************************************/
void ToggleShowBoundingBoxMode()
{
	if (g_BBShowMode)
	{
		RemoveAll_BoundingBoxOutline();			//Deletes all the debugComponent and entity
	}
	else
	{
		ShowAll_BoundingBoxOutline();			//Scans for possible mesh outlines
	}
	g_BBShowMode = !g_BBShowMode;
}

