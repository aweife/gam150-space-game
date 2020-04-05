/**********************************************************************************
* \file			Global.h
* \brief		Stores global variables about gameplay, time and window size
* \author		Jun Yi,			Chong,		100% Code Contribution
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include <Windows.h>
#include "AEVec2.h"

//------------------------------------
// Gameplay Global Variables
//------------------------------------

//Boolean Based
extern bool		g_DebugEditor;					// Should the game show a console window
extern bool		g_GamePause;					// Is the game paused?
extern bool		g_BBShowMode;					// Display all outline of mesh rigidbody
extern bool		g_isFullScreen;					// Is the game in fullscreen
extern bool		g_isMute;						// Is the game audio muted

//Time Based
extern float		g_dt;						// Delta Time for game
extern float		g_appTime;					// Time since game was started		

//Window Based
extern float		g_WorldMinX;				// World(Game) screen minimum X coordinates
extern float		g_WorldMaxX;				// World(Game) screen maximum X coordinates
extern float		g_WorldMinY;				// World(Game) screen minimum Y coordinates
extern float		g_WorldMaxY;				// World(Game) screen maximum Y coordinates
extern RECT			g_WindowRect;				// Size of windowRect in pixels 
extern long			g_WindowWidth;				// Width  ^
extern long			g_WindowHeight;				// Height ^

extern AEVec2 defaultAEVec2;
extern float defaultFloat;


void Global_InitWindowSize(bool isFullScreen);


void Global_ToggleWindowed();

void Global_UpdateWindowSize();

void TogglePause();

void ToggleShowBoundingBoxMode();



