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
#include "../Systems/UISystem.h"
#include "../Player/PlayerManager.h"
#include "LevelManager.h"
#include "AudioManager.h"								// Testing audio

#include "../ECS/Factory.h"
#include "../ECS/Core.h"
#include "../Systems/UISystem.h"
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

		if (AEInputCheckTriggered(AEVK_ESCAPE) && currentState != GS_SPLASHSCREEN && currentState != GS_MAINMENU && currentState != GS_LOADINGSCREEN
			&& PlayerManager::player && !g_isSecondaryMenu)
		{
			TogglePause();
			g_GamePause ? UIEventsManager::Broadcast(new Events::TogglePause(true)) 
				: UIEventsManager::Broadcast(new Events::TogglePause(false));
			AudioManager::TogglePause(g_GamePause);
		}
		else if (AEInputCheckTriggered(AEVK_ESCAPE) && currentState == GS_MAINMENU)
		{
			Factory_UI::CreateUI_ExitConfirmation();
		}
		else if (AEInputCheckTriggered(AEVK_ESCAPE) && currentState == GS_UPGRADE)
		{
			TogglePause();
			g_GamePause ? UIEventsManager::Broadcast(new Events::TogglePause(true))
				: UIEventsManager::Broadcast(new Events::TogglePause(false));
			AudioManager::TogglePause(g_GamePause);
		}
		//if (AEInputCheckTriggered(AEVK_ESCAPE))
		//{
		//	if (currentState == GS_MAINMENU)
		//	{
		//		GSM_QuitGame();							//NEXT TIME PUT IN A UI HERE TO COMFIRM ACTION!
		//	}
		//	else
		//	{
		//		GSM_ChangeState(GS_MAINMENU);
		//	}
		//}
		//if (AEInputCheckTriggered(AEVK_R))
		//{
		//	//GSM_RestartLevel();					//NEXT TIME PUT IN A UI HERE TO COMFIRM ACTION!
		//}

		if (!g_GamePause)
		{
			//Debug functionality
		//if (AEInputCheckTriggered(AEVK_0))			//Show all mesh outline
		//{
		//	ToggleShowBoundingBoxMode(); 
		//}
			if (AEInputCheckTriggered(AEVK_9))			
			{
				GSM_ChangeState(GS_UPGRADE);
				//GSM_LoadingTransition(GS_UPGRADE);
				//Factory_UI::Create_ChooseThree({ 0,0 });
			}
		/*if (AEInputCheckTriggered(AEVK_8))
		{
			std::shared_ptr<UISystem> uiSys(std::static_pointer_cast<UISystem>(Core::Get().GetSystem<UISystem>()));
			uiSys->DeleteUpgradeWindow();
		}*/
			if (AEInputCheckTriggered(AEVK_1))
			{
				if (Core::Get().GetComponent<cRangeWeapon>(PlayerManager::player)->_currWeapon != WeaponType::laser)
				{
					Core::Get().GetComponent<cRangeWeapon>(PlayerManager::player)->_currWeapon = WeaponType::laser;
					Core::Get().GetComponent<cRangeWeapon>(PlayerManager::player)->_delayBetweenAttacks = 0.0f;
					Core::Get().GetComponent<cRangeWeapon>(PlayerManager::player)->_ammo = 1;
				}

			}
			if (AEInputCheckTriggered(AEVK_2))
			{
				if (Core::Get().GetComponent<cRangeWeapon>(PlayerManager::player)->_permenanceProjectile)
				{
					Core::Get().EntityDestroyed(Core::Get().GetComponent<cRangeWeapon>(PlayerManager::player)->_permenanceProjectile);
					Core::Get().GetComponent<cRangeWeapon>(PlayerManager::player)->_permenanceProjectile = 0;
				}
				Core::Get().GetComponent<cRangeWeapon>(PlayerManager::player)->_currWeapon = WeaponType::pistol;
				Core::Get().GetComponent<cRangeWeapon>(PlayerManager::player)->_delayBetweenAttacks = 0.2f;
			}

		}
		// -----------------------------------------------------------------------
		// Mouse Controls
		// -----------------------------------------------------------------------
		AEInputGetCursorPosition(&mousePosX, &mousePosY);

		Editor_TrackVariable("mouse Screen X", mousePosX);
		Editor_TrackVariable("mouse Screen Y", mousePosY);
		
		float yOffset = 20.0f * static_cast<int>(!g_isFullScreen);

		if(!g_GamePause) UIEventsManager::Broadcast(new Events::OnMouseHover(mousePosX - g_WorldMaxX, -1 * (mousePosY - g_WorldMaxY + yOffset)));
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			if (!UIEventsManager::Broadcast(new Events::OnMouseClick(mousePosX - g_WorldMaxX, -1 * (mousePosY - g_WorldMaxY + yOffset))))
			{
				if (!g_GamePause) mouseLTrigger = true;
			}
			else
			{
				if (!g_GamePause) mouseLTrigger = false;
			}
		}
		else if(!g_GamePause)
		{
			if (AEInputCheckCurr(AEVK_LBUTTON))
			{
				if (!g_GamePause) mouseLTrigger = true;			//Auto Fire Bullets
			}
			else
			{
				if (!g_GamePause) mouseLTrigger = false;
			}
		}
		if(!g_GamePause) mouseRTrigger = AEInputCheckCurr(AEVK_RBUTTON);					//JY: Check if selecting UI.. otherwise go to player
	
	}
}
	
