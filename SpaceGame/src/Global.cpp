/*********************************************************************************
* \file			Global.cpp
* \author		Ang Wei Feng, Chong Jin Kiat, Chong Jun Yi, Farzaana Binte Roslan
* \version		1.0
* \date			18/01/2019
* \par			Data storage Code
* \note			Course: GAM150
* \brief		Stores global variables about the game
				- Game Start Time (Time when exe was lauched)
				-

* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "Global.h"
#include "Tools/Console.h"
#include "AEEngine.h"			//Time

namespace Global 
{
	bool gGamePause;				// GameStatePaused
	double gStartTime;				// Time when game was launched

/******************************************************************************/
/*!
  \brief	Get data when game starts
*/
/******************************************************************************/
	void Global_Init()
	{
		AEGetTime(&Global::gStartTime);
	}

/******************************************************************************/
/*!
  \brief	Pause or unpause the game .... may need to move to gamestate??
*/
/******************************************************************************/
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