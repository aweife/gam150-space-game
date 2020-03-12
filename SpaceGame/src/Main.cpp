/*********************************************************************************
* \file			Main.cpp
* \author		Ang Wei Feng, Chong Jin Kiat, Chong Jun Yi, Farzaana Binte Roslan
* \version		1.0
* \date			18/01/2019
* \par			MAIN
* \note			Course: GAM150
* \brief		Entry point for Game executable "End Of Space" by Moon Base
				- Initalise Window, Console, ECS Game Engine
				- Game State Loop, Game loop
				- Program Cleanup

* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

// Includes
#include <crtdbg.h>						// For Memory Leak
#include "AEEngine.h"					// AlphaEngine
#include "Global.h"						// Global variables 
#include "Tools/Editor.h"				// Editor for gameplay
#include "Tools/Console.h"				// Debug logger
#include "ECS/Core.h"					// Initalise Game Engine
#include "Managers/GameStateManager.h"  // Control Game State Flow
#include "Managers/InputManager.h"		// Recieve Input from AlphaEngine
#include "Managers/ResourceManager.h"	// Generate Mesh and Load in Texture

#include "Managers/AudioManager.h"
#include "Managers/UpgradeManager.h"
#include "Tools/MemoryLeak.h"

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

#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);				//Memory Leak Checker
	g_DebugEditor = true;														//Set Console while in debug mode
#endif

	// -----------------------------------------------------------------------
	// Initialization of Application Window
	// -----------------------------------------------------------------------
	AESysInit(hInstance, nCmdShow, 1280, 720, g_DebugEditor, 60, true, NULL);	// Using custom window procedure
	AESysSetWindowTitle("Master Branch");										// Changing the window title
	AESysReset();																// reset the system modules
	AEGfxSetBackgroundColor(0.07f, 0.04f, 0.22f);								// Set Dark Purple BG 

#if defined(DEBUG) | defined(_DEBUG)
	Console_Init();																//Resize console window
	Editor_Init();
#endif

	// -----------------------------------------------------------------------
	// Initialization of Game 
	// -----------------------------------------------------------------------
	Global_Init();																// Init time, windowSize...
	Core::Get().Core_Init();													// Initalise Game Engine ECS
	ResourceManager::Init();													// Load in Bare Minimum
	UpgradeManager::Init_UpgradeDatabase();
	AudioManager::Init();
	AudioManager::Loadsound("res/SFX/Confirm.wav"); // to be removed
	float timer = 0.0f;

	GSM_Init(GS_MAINMENU);														// Initalise Game StateManager

	// -----------------------------------------------------------------------
	// GAME STATE LOOP
	// -----------------------------------------------------------------------
	while (currentState != GS_QUIT)
	{
		if (currentState != GS_RESTART)
		{
			GSM_Update();														// Reassign function pointers
			fpLoad();															// Load Assets needed for level
		}
		else
		{
			nextState = previousState;											// Restart the level
			currentState = previousState;
		}
		fpInit();																// INITALISE data for current game state
		
		// -----------------------------------------------------------------------
		// Main Game loop
		// -----------------------------------------------------------------------
		while (nextState == currentState)
		{
			timer += g_dt;   // to be removed
			if (timer > 1.0f)
			{
				AudioManager::PlayOneShot();
				timer = 0.0f;
			}


			// Informing the system about the loop's start ***********************
			AESysFrameStart();			

			Editor_Update();										// Editor Update	
			AEInputUpdate();										// Handling Input
			InputManager::Update();

			if (!g_GamePause)										// Only update game if NOT PAUSED
			{
				fpUpdate();											// Game State Update Logic
			}
			fpDraw();												// Game State Render Graphics 
			Editor_Render();										// Render any helper features for editor

			// Informing the system about the loop's end *************************
			AESysFrameEnd();							

			// Get deltatime
			g_dt = static_cast<f32>(AEFrameRateControllerGetFrameTime());
			g_appTime += g_dt;

			// Check if forcing the application to quit
			// See Input for Esc Key triggered to exit game
			if ( 0 == AESysDoesWindowExist())
			{
				nextState = GS_QUIT;
			}
		}

		fpFree();													// Reset Game State Data
		if (nextState != GS_RESTART)
		{
			fpUnload();												// Unload assets and memory
		}
		previousState = currentState;
		currentState = nextState;
	}

	// -----------------------------------------------------------------------
	// Clean up for all buffer and memory
	// -----------------------------------------------------------------------
	ResourceManager::Unload();
	UpgradeManager::Cleanup_UpgradeDatabase();
	AudioManager::Shutdown();
	Console_CleanUp();
	Core::Get().Core_Unload();						// free all core system
	AESysExit();									// free the system
}

