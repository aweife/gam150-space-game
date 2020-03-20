/**********************************************************************************
* \file			MainMenu.h
* \brief		Game State for Main Menu
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*				Long Description
*				- Play, Options, Credits, Exit
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "MainMenu.h"
#include "../ECS/Factory.h"
#include "../ECS/Core.h"
#include "../Managers/UIEventsManager.h"


void MainMenu_Load()
{
	Create_MainMenuInterface();
	Factory::CreateMenuPlayer();
	Factory_Map::Generate_StarField_Menu();
}
void MainMenu_Init()
{
	AEGfxSetCamPosition(0, 0);
}
void MainMenu_Update()
{
	Core::Get().Core_Update();
}
void MainMenu_Draw()
{
	Core::Get().Core_Render();
}
void MainMenu_Free()
{

}
void MainMenu_Unload()
{
	UIEventsManager::Cleanup();
	Core::Get().DestroyAllEntity();
}

#include "../Systems/UISystem.h"
//Placed here since there is only one main menu
void Create_MainMenuInterface()
{
	AEVec2 mmAnchor = ScreenBasedCoords(0,-250, UI_ANCHOR::CENTER);
	Factory_UI::Create_MM_BeginCampaignUI({ mmAnchor.x-350, mmAnchor.y });
	Factory_UI::Create_MM_OptionsUI({ mmAnchor.x - 120, mmAnchor.y});
	Factory_UI::Create_MM_CreditsUI({ mmAnchor.x + 120 , mmAnchor.y });
	Factory_UI::Create_MM_Quit({ mmAnchor.x + 350, mmAnchor.y });

	AEVec2 mmAnchor2 = ScreenBasedCoords(0, 150, UI_ANCHOR::CENTER);
	Factory_UI::Create_GameLogo( mmAnchor2, {400,240});

	//Factory::CreateEnemy1(0, 2);
}