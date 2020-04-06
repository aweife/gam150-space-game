/**********************************************************************************
* \file			UpgradeLevel.cpp
* \brief		Game State for upgrade level Screen
* \author		Jun Yi,			Chong,		100% Code Contribution
*
*				Long Description
*				- Slot machine
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "UpgradeLevel.h"
#include "../ECS/Factory.h"
#include "../Managers/GameStateManager.h"
#include "../Managers/UIEventsManager.h"
#include "../Managers/LevelManager.h"
#include "../Managers/AudioManager.h"
unsigned int loadingForNextLevel = GS_NULL;
bool upgradeFinish;

void UpgradeLvl_Load()
{
	Factory::CreateMenuPlayer();
	Factory_Map::Generate_StarField();
	Factory_UI::Create_ChooseThree({0, 0 }, 2);
	AudioManager::LoadSound("res/BGM/cinescifi.wav", true);

}

void UpgradeLvl_Init()
{
	AudioManager::PlayBGM("res/BGM/cinescifi.wav", 0.25f);

	AEGfxSetCamPosition(0, 0);
	upgradeFinish = false;
}

void UpgradeLvl_Update()
{
	Core::Get().Core_Update();
	if (upgradeFinish && loadingForNextLevel != GS_NULL)
	{
		GSM_LoadingTransition(loadingForNextLevel);
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
	LevelManager::Clear_StarField();
	UIEventsManager::Cleanup();
	Core::Get().DestroyAllEntity();
}
