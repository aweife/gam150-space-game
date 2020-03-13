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
	AEVec2 mmAnchor = ScreenBasedCoords(0,-300, UI_ANCHOR::CENTER);
	Factory_UI::Create_MM_BeginCampaignUI({ mmAnchor.x-300, mmAnchor.y });
	Factory_UI::Create_MM_OptionsUI({ mmAnchor.x - 100, mmAnchor.y});
	Factory_UI::Create_MM_CreditsUI({ mmAnchor.x + 100 , mmAnchor.y });
	Factory_UI::Create_MM_Quit({ mmAnchor.x + 300, mmAnchor.y });

	AEVec2 mmAnchor2 = ScreenBasedCoords(0, 200, UI_ANCHOR::CENTER);
	Factory_UI::Create_GameLogo( mmAnchor2, {400,240});

	//Factory::CreateEnemy1(0, 2);
}