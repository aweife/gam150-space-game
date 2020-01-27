#include "Global.h"
#include "Tools/Console.h"
#include "AEEngine.h"			//Time

namespace Global 
{
	bool gGamePause;
	double gStartTime;

	void Global_Init()
	{
		AEGetTime(&Global::gStartTime);
	}

	void TogglePause()
	{
		if (gGamePause) 
		{
			Console_CoutDetailed("Game is Unpaused", -1, " ");
		}
		else
		{
			Console_CoutDetailed("Game is Paused", -1, " ");
		}
		gGamePause = !gGamePause;
	}
}