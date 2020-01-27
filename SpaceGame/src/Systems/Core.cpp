#include "GameObjectManager.h"
#include "Core.h"

void Core_Init()
{
	//Create all the systems and manager
	GameObjectManager::GetInstance()->CreateGameObject("Hello");
	GameObjectManager::GetInstance()->CreateGameObject("World");

	GameObjectManager::GetInstance()->GenerateGameObjectList();

}


void Core_Update()
{
	GameObjectManager::GetInstance()->GenerateComponentList(0);
}

void Core_Unload()
{
	GameObjectManager::DestroyInstance();
}