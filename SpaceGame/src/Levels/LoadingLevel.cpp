#include "LoadingLevel.h"
#include "../ECS/Factory.h"
#include "../ECS/Core.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/UIEventsManager.h"
#include "../Managers/GameStateManager.h"

unsigned int loadingForState = GS_NULL;

void LoadingLvl_Load()
{
	Factory_UI::CreateUI_Text(100, -150, "Loading Level...");
	Factory_UI::CreateBackground_Load();
}

void LoadingLvl_Init()
{
	//loadingForState = GS_LEVEL1;					//REMOVE IN FUTURE
	ResourceManager::loadingProgress = 0;
	ResourceManager::loadingCompleted = false;
}

void LoadingLvl_Update()
{
	ResourceManager::Update(loadingForState);
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
