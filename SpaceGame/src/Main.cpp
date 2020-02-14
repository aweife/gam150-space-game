/*********************************************************************************
* \file			Main.cpp
* \author		Ang Wei Feng, Chong Jin Kiat, Chong Jun Yi, Farzaana Binte Roslan
* \version		1.0
* \date			18/01/2019
* \par			MAIN
* \note			Course: GAM150
* \brief		Entry point for Game executable "End Of Space" by Moon Base
				- Initalise Window, Console, hardware
				- Game State Loop, Game loop
				- Program Cleanup

* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
// ---------------------------------------------------------------------------
// Includes
#include <crtdbg.h>						// For Memory Leak
#include "AEEngine.h"					// AlphaEngine
#include "Global.h"						// Global variables 
#include "Tools/Editor.h"				// Editor for gameplay
#include "Tools/Console.h"				// Debug logger
#include "ECS/Core.h"
#include "Managers/GameStateManager.h"
#include "Input/Input.h"

// ---------------------------------------------------------------------------
// Libraries
//#pragma comment (lib, "Alpha_Engine.lib")
// ---------------------------------------------------------------------------

/******************************************************************************/
/*!
  \brief	Entry point for Game executable "End Of Space"
*/
/******************************************************************************/
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// -----------------------------------------------------------------------
	// Variable declaration

	int gGameRunning = 1;
	int gDebugEditor = 0;

	// Variable declaration end
	// -----------------------------------------------------------------------

#if _DEBUG
	gDebugEditor = 1; //Set Console to active while in debug mode
#endif

	// -----------------------------------------------------------------------
	// Initialization

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1280, 720, gDebugEditor, 60, true, NULL);
	// Changing the window title
	AESysSetWindowTitle("Master Branch");

#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);		//Memory Leak Checker
	Console_Init();						//Resize console window
	Editor_Init();
#endif

	Global_Init();				// Get start time of game program
	Core::Get().Core_Init();

	// reset the system modules
	AESysReset();
	AEGfxSetBackgroundColor(0.6, 0.0, 0.8);
	
	//AEGameStateMgrInit();

	// Initialization end
	// -----------------------------------------------------------------------


	//TODO: Implement GSM
	// -----------------------------------------------------------------------
	GSM_Init(GS_LEVEL1);

	// Game Loop
	while (currentState != GS_QUIT)
	{
		if (currentState != GS_RESTART)
		{
			GSM_Update();
			fpLoad();
		}
		else
		{
			nextState = previousState;
			currentState = previousState;
		}
		fpInit();								//INITALISE data for current game state
		InputInit();
		while (nextState == currentState)
		{
			// Informing the system about the loop's start
			AESysFrameStart();

			// Handling Input
			AEInputUpdate();
			InputUpdate();

			//TODO : Need to tidy this up next time
			if (AEInputCheckTriggered(AEVK_P)) {
				TogglePause();
			}
			else if (gGamePause)
			{
				AESysFrameEnd();
				// check if forcing the application to quit
				if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
					gGameRunning = 0;
				continue;
			}
			// -----------------------------------------------------------------------
			// Game loop update
			Editor_Update();
			fpUpdate();
			// Game loop update end
			// -----------------------------------------------------------------------

			// -----------------------------------------------------------------------
			// Game loop draw
			fpDraw();
			// Game loop draw end
			// -----------------------------------------------------------------------
			// Informing the system about the loop's end
			AESysFrameEnd();

			// Get deltatime
			g_dt = static_cast<f32>(AEFrameRateControllerGetFrameTime());
			g_appTime += g_dt;

			// check if forcing the application to quit
			if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			{
				gGameRunning = 0;
			}
		}
		fpFree();

		if (nextState != GS_RESTART)
		{
			fpUnload();
		}
		previousState = currentState;
		currentState = nextState;
	}
	// -----------------------------------------------------------------------

	Console_CleanUp();
	Core::Get().Core_Unload();			// free all core system
	//Console_CleanUp();
	AESysExit();			// free the system
}

