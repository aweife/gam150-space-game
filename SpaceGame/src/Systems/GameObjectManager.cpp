#include "GameObjectManager.h"
#include <string>
#include "../Tools/Console.h"
#include "../Components/MeshComponent.h"
#include "MemoryPool.h"

// Null, because instance will be initialized on demand. 
GameObjectManager* GameObjectManager::instance = 0;

GameObjectManager& GameObjectManager::GetInstance()
{
	if (instance == 0)
	{
		instance = new GameObjectManager();
	}

	AE_ASSERT(instance);	//Assert if fail to create GameManager
	return *instance;
}

GameObjectManager::GameObjectManager()
	:gObjCount{0}
{
	//Need this for singleton instance
}

void GameObjectManager::DestroyInstance()
{
	instance->gObjList.clear();
	for (auto i = instance->gObjList.begin(); i != instance->gObjList.end();)
	{
	}
	delete(instance);
}

void GameObjectManager::CreateGameObject(std::string name)
{
	//this is so bad....rewrite
	GameObject a = GameObject(name, gObjCount);
	gObjList.push_back(a);

	gObjCount++;
}

GameObject& GameObjectManager::GetGameObject(short index)
{
	return gObjList.at(index);
}

void GameObjectManager::GenerateGameObjectList() const
{
	if (gObjList.empty()) return;
	Console_Cout("---Generating GameObject List---");
	for (auto i = gObjList.begin(); i != gObjList.end(); ++i)
	{
		Console_Cout(i->_name);
	}
}

void GameObjectManager::GenerateComponentList(short index) const
{
	if (gObjList.empty()) return;
	Console_Cout("---Generating GameObject Internal Component ---");
	const GameObject& target = gObjList.at(index);
	
	for (auto i = target.componentList.begin(); i != target.componentList.end(); ++i)
	{
		Console_Cout(i->_name);
	}
}
