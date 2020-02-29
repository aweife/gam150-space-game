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

void Global_Init();

void TogglePause();

void ToggleShowBoundingBoxMode();



