#include "LoadingLevel.h"
#include "../ECS/Factory.h"
#include "../ECS/Core.h"
#include "../Managers/ResourceManager.h"
#include <queue>

unsigned int loadingForState = GS_NULL;
std::queue<ENTITY> entityToDestroy;

void LoadingLvl_Load()
{
	entityToDestroy.push(Factory::CreateUI_Text(100, -150, "Loading Level..."));
	entityToDestroy.push(Factory::CreateBackground_Load());
}

void LoadingLvl_Init()
{
	loadingForState = GS_LEVEL1;					//REMOVE IN FUTURE
	ResourceManager::loadingProgress = 0;
	ResourceManager::loadingCompelete = false;
}

void LoadingLvl_Update()
{
	ResourceManager::Update(GS_LEVEL1);
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
	ResourceManager::loadingCompelete = true;
}

void LoadingLvl_Unload()
{
	while (entityToDestroy.size() > 0)
	{
		ENTITY destroy = entityToDestroy.front();
		Core::Get().EntityDestroyed(destroy);
		entityToDestroy.pop();
	}
}
