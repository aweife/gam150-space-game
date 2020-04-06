/**********************************************************************************
* \file			LoadingLevel.cpp
* \brief		Game State for Loading Level
* \author		Jun Yi,			Chong,		100% Code Contribution
*				
*				Long Description
*				- Provide a loading screen
*				- While loading assets within the delta time of each frame
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "LoadingLevel.h"
#include "../ECS/Factory.h"
#include "../ECS/Core.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/UIEventsManager.h"
#include "../Managers/GameStateManager.h"
#include "../Systems/UISystem.h"							//edit text

unsigned int loadingForState = GS_NULL;
ENTITY loadingText = 0;

void LoadingLvl_Load()
{
	loadingText = Factory_UI::CreateUI_Text(0, -150, "Loading Level...");
	Factory_UI::CreateBackground_Load();
}

void LoadingLvl_Init()
{
	ResourceManager::loadingProgress = 0;
	ResourceManager::loadingCompleted = false;
	ResourceManager::loadingStage = 0;
}

void LoadingLvl_Update()
{
	ResourceManager::Update(loadingForState);
	EditText(loadingText, "Loading Level...", ResourceManager::loadingProgress);
	if (ResourceManager::loadingProgress >= 100)
	{
		GSM_ChangeState(loadingForState);
	}
}

void LoadingLvl_Draw()
{
	Core::Get().Core_Render();
}

void LoadingLvl_Free()
{
	loadingForState = GS_NULL;
	ResourceManager::loadingProgress = 100;
	ResourceManager::loadingCompleted = true;
}

void LoadingLvl_Unload()
{
	UIEventsManager::Cleanup();
	Core::Get().DestroyAllEntity();
}
