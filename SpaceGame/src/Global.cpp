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
#include "Tools/Editor.h"								//Change windowed size
//Game State
bool		g_DebugEditor	= false;					// Should the game show a console window
bool		g_GamePause		= false;					// Is the game paused?
bool		g_BBShowMode	= false;					// Display all outline of mesh rigidbody
bool		g_isFullScreen	= false;					// Is the game in fullscreen
bool		g_isMute		= false;					// Is the game audio muted
bool		g_isSecondaryMenu = false;					// Is accessing secondary menu


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
  \brief	Estimate the size of fullscreen
			Since AE Mouse Input Space does not update with Fullscreen
*/
/******************************************************************************/
void Global_InitWindowSize(bool isFullScreen)
{
	RECT   desktopRect;
	GetWindowRect(GetDesktopWindow(), &desktopRect);

	if (isFullScreen)
	{
		g_isFullScreen = true;
		g_WindowWidth = desktopRect.right - desktopRect.left;
		g_WindowHeight = desktopRect.bottom - desktopRect.top;
	}
	else
	{
		g_isFullScreen = false;
		g_WindowWidth = 1280;
		g_WindowHeight = 720;
	}

}

//called from option screen ONLY
void Global_ToggleWindowed()
{
	AEToogleFullScreen(!g_isFullScreen);
	if (g_isFullScreen)
	{
		// AE values cannot be modified
		//Editor_SetSize(1280, 720);
	}
	Global_InitWindowSize(!g_isFullScreen);
	Global_UpdateWindowSize();
}

/******************************************************************************/
/*!
  \brief	Get data when game starts
*/
/******************************************************************************/
void Global_UpdateWindowSize()
{
	GetWindowRect(AESysGetWindowHandle(), &g_WindowRect);		// Get Size of the windows display
	g_WindowWidth = g_WindowRect.right - g_WindowRect.left;		// Calculate window Width
	g_WindowHeight = g_WindowRect.bottom - g_WindowRect.top;	// Calculate window Height...-30 for the title
	
	g_WorldMinX = g_WindowWidth  / -2.0f;					// World minimum X coordinates
	g_WorldMinY = g_WindowHeight / -2.0f;					// World minimum Y coordinates 
	g_WorldMaxX = g_WindowWidth  / 2.0f;					// World maximum X coordinates
	g_WorldMaxY = g_WindowHeight / 2.0f;					// World maximum Y coordinates
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

