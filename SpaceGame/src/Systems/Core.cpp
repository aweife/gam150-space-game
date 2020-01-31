#include "Core.h"
#include "GameObjectManager.h"
#include "MemoryPool.h"

#include "..//Components/MeshComponent.h"

void Core_Init()
{
	//Create all the systems and manager instances
	GameObjectManager::GetInstance();
	MemoryPool::GetInstance();

	//Testing ... remove later
	GameObjectManager::GetInstance().CreateGameObject("Hello");
	GameObjectManager::GetInstance().CreateGameObject("World");

	GameObjectManager::GetInstance().GenerateGameObjectList();

	GameObjectManager& hello = GameObjectManager::GetInstance();
	hello.GetGameObject(0).AddComponent<MeshComponent>();
	hello.GetGameObject(0).AddComponent<MeshComponent>();
	hello.GetGameObject(0).AddComponent<MeshComponent>();
	hello.GetGameObject(0).AddComponent<MeshComponent>();

	hello.GetGameObject(0).RemoveComponent<MeshComponent>();
	hello.GetGameObject(0).RemoveComponent<MeshComponent>();
	hello.GetGameObject(0).RemoveComponent<MeshComponent>();
	hello.GetGameObject(0).RemoveComponent<MeshComponent>();
}


void Core_Update()
{
	//Remove after testing

	GameObjectManager& hello = GameObjectManager::GetInstance();
	//hello.GetGameObject(0).AddComponent<MeshComponent>();
	//hello.AddComponent<MeshComponent>(hello.GetGameObject(0));
	//GameObjectManager::GetInstance().GenerateComponentList(0);
}

void Core_Unload()
{
	GameObjectManager::DestroyInstance();
	MemoryPool::DestroyInstance();
}