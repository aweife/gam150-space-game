/*********************************************************************************
* \file			Input.cpp
* \author		Chong Jin Kiat (Main Author - Gameplay)
* \author       Chong Jun Yi (Integrate UI and Debugging)
* \version		2.0
* \date			17/02/2020
* \par			Input 
* \note			Course: GAM150
* \brief		Handles global input. All related player logic will pass to PlayerManager
				- player input during gameplay
				- player input during upgrades (no game simulation)
				- player input during menus

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/

#include "InputManager.h"								// Self Header
#include "AEEngine.h"									// AE Input
#include "../Managers/GameStateManager.h"				// Exit Game or Restart
#include "../Global.h"									// delta time, windowSize
#include "../Tools/Editor.h"							// Track Variable + Mesh Show mode

#include "../Managers/CameraManager.h"					//Testing....remove once screenshake is done
#include "UIEventsManager.h"							//Testing events calling

namespace InputManager
{
	int			mousePosX			= 0;				// Computer mouse screen position in X coordinates
	int			mousePosY			= 0;				// Computer mouse screen position in Y coordinates
	bool		mouseRTrigger		= false;
	bool		mouseLTrigger		= false;

	/******************************************************************************/
	/*!
		\brief Check what mouse or keyboard buttons are being pressed
	*/
	/******************************************************************************/
	void Update()
	{
		// -----------------------------------------------------------------------
		// Non-Gameplay Keyboard Controls ... Pause, Exit
		// -----------------------------------------------------------------------

		if (AEInputCheckTriggered(AEVK_P)) {
			TogglePause();
		}
		if (AEInputCheckTriggered(AEVK_ESCAPE))
		{
			GSM_QuitGame();							//NEXT TIME PUT IN A UI HERE TO COMFIRM ACTION!
		}
		if (AEInputCheckTriggered(AEVK_R))
		{
			//GSM_RestartLevel();					//NEXT TIME PUT IN A UI HERE TO COMFIRM ACTION!
		}

		//Debug functionality
		if (AEInputCheckTriggered(AEVK_0))			//Show all mesh outline
		{
			ToggleShowBoundingBoxMode(); 
		}

		//Testing...remove once done
		if (AEInputCheckTriggered(AEVK_S))
		{
			CameraManager::StartCameraShake();
		}
		if (AEInputCheckTriggered(AEVK_E))
		{
			UIEventsManager::Broadcast(new Events::OnHealthChange(22.0f));
		}

		// -----------------------------------------------------------------------
		// Mouse Controls
		// -----------------------------------------------------------------------
		AEInputGetCursorPosition(&mousePosX, &mousePosY);

		Editor_TrackVariable("mouse Screen X", mousePosX);
		Editor_TrackVariable("mouse Screen Y", mousePosY);

		if (AEInputCheckCurr(AEVK_LBUTTON))
		{
			if (!UIEventsManager::Broadcast(new Events::OnMouseClick(mousePosX - g_WorldMaxX, -1 * (mousePosY - g_WorldMaxY))))
			{
				mouseLTrigger = true;
			}
			else
			{
				mouseLTrigger = false;
			}
		}
		else
		{
			mouseLTrigger = false;
		}
		mouseRTrigger = AEInputCheckCurr(AEVK_RBUTTON);					//JY: Check if selecting UI.. otherwise go to player
	
	}
}
	
