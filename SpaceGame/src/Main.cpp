// ---------------------------------------------------------------------------
// Includes
#include <crtdbg.h>        // For Memory Leak
#include "AEEngine.h"
#include "Global.h"
#include "Tools/Editor.h"
#include "Tools/Console.h"
#include "Levels/Level1.h"
#include "Systems/Core.h"				//Core System Controller

// ---------------------------------------------------------------------------
// Libraries
//#pragma comment (lib, "Alpha_Engine.lib")
// ---------------------------------------------------------------------------
// Main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	///////////////////////
	// Variable declaration

	int gGameRunning = 1;
	int gDebugEditor = 0;

	// Variable declaration end
	///////////////////////////

#if _DEBUG
	gDebugEditor = 1;
#endif

	/////////////////
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

	Core_Init();						// Init all systems
	Global::Global_Init();				// Get start time of game program


	// reset the system modules
	AESysReset();
	AEGfxSetBackgroundColor(0.5, 0.5, 0.5);

	//AEGameStateMgrInit();

	// Initialization end
	/////////////////////


	//TODO: Implement GSM

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		//TODO : Need to tidy this up next time
		if (AEInputCheckTriggered(AEVK_P)) {
			Global::TogglePause();
		}
		else if (Global::gGamePause)
		{
			AESysFrameEnd();
			// check if forcing the application to quit
			if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
				gGameRunning = 0;
			continue;
		}
		///////////////////
		// Game loop update
		Editor_Update();
		Core_Update();
		Level1_Update();
		// Game loop update end
		///////////////////////

		//////////////////
		// Game loop draw
		// Game loop draw end
		/////////////////////
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	Console_CleanUp();
	Core_Unload();			// free all core system
	
	AESysExit();			// free the system
}

