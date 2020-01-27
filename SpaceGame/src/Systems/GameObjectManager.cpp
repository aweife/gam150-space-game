#include "GameObjectManager.h"
#include "../Tools/Console.h"
#include <string>
#include "../Components/MeshComponent.h"

// Null, because instance will be initialized on demand. 
GameObjectManager* GameObjectManager::instance = 0;

GameObjectManager* GameObjectManager::GetInstance()
{
	if (instance == 0)
	{
		instance = new GameObjectManager();
	}

	return instance;
}

GameObjectManager::GameObjectManager()
	:gObjCount{0}
{
	//Need this for singleton instance
}

void GameObjectManager::DestroyInstance()
{
	delete(instance);
}

void GameObjectManager::CreateGameObject(std::string name)
{
	GameObject a = GameObject(name, gObjCount);
	gObjList.push_back(a);

	AddComponent(a, MeshComponent());
	gObjCount++;
}

void GameObjectManager::GenerateGameObjectList() const
{
	Console_Cout("---Generating GameObject List---");
	for (auto i = gObjList.begin(); i != gObjList.end(); ++i)
	{
		Console_Cout(i->_name);
	}
}

void GameObjectManager::GenerateComponentList(short index) const
{
	Console_Cout("---Generating GameObject Internal Component ---");
	
	GameObject a = gObjList.at(index);
	for (auto i = a.componentList.begin(); i != a.componentList.end(); ++i)
	{
		Console_Cout(i->_name);
	}
}

void GameObjectManager::AddComponent(GameObject& gObj, const Component& addComponent)
{
	gObj.componentList.push_back(addComponent);
}