#include "MainMenu.h"
#include "../ECS/Factory.h"
#include "../ECS/Core.h"
#include "../Managers/UIEventsManager.h"


void MainMenu_Load()
{
	Create_MainMenuInterface();
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
	AEVec2 mmAnchor = ScreenBasedCoords(200,100, UI_ANCHOR::BOTTOMLEFT);
	Factory_UI::Create_MM_BeginCampaignUI({ mmAnchor.x, mmAnchor.y });
	Factory_UI::Create_MM_OptionsUI({ mmAnchor.x + 200, mmAnchor.y});
	Factory_UI::Create_MM_CreditsUI({ mmAnchor.x + 400 , mmAnchor.y });
	Factory_UI::Create_MM_Quit({ mmAnchor.x + 600, mmAnchor.y });

	AEVec2 mmAnchor2 = ScreenBasedCoords(0, 200, UI_ANCHOR::CENTER);
	Factory_UI::Create_GameLogo( mmAnchor2, {200,120});

	//Factory::CreateEnemy1(0, 2);
}