#include "UpgradeLevel.h"
#include "../ECS/Factory.h"
#include "../Managers/GameStateManager.h"
#include "../Managers/UIEventsManager.h"

unsigned int loadingForNextLevel = GS_NULL;
bool upgradeFinish;

void UpgradeLvl_Load()
{
	Factory::CreateMenuPlayer();
	Factory_Map::Generate_StarField_Menu();
	Factory_UI::Create_ChooseThree({ 0,0 });
}

void UpgradeLvl_Init()
{
	AEGfxSetCamPosition(0, 0);
	upgradeFinish = false;
}

void UpgradeLvl_Update()
{
	Core::Get().Core_Update();
	if (upgradeFinish && loadingForNextLevel != GS_NULL)
	{
		GSM_ChangeState(loadingForNextLevel);
	}
}

void UpgradeLvl_Draw()
{
	Core::Get().Core_Render();
}

void UpgradeLvl_Free()
{
	loadingForNextLevel = GS_NULL;
	upgradeFinish = false;
}

void UpgradeLvl_Unload()
{
	UIEventsManager::Cleanup();
	Core::Get().DestroyAllEntity();
}
