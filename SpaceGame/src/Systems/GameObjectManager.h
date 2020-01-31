#pragma once
#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H
#include <vector>
#include "../GameObjects/GameObject.h"

class GameObjectManager
{
private:
	/* Here will be the instance stored. */
	static GameObjectManager* instance;
	std::vector<GameObject> gObjList;
	short gObjCount;

	/* Private constructor to prevent instancing. */
	GameObjectManager();

public:

	/* Static access method. */
	static GameObjectManager& GetInstance();
	static void DestroyInstance();
	void CreateGameObject(std::string name);
	GameObject& GetGameObject(short index);
	void GenerateGameObjectList() const;
	void GenerateComponentList(short index) const;

	//Need to specify source code in header due to compiler accessibility
	//https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
	//Example:GameObjectManager.AddComponent<MeshComponent>(GameObject);
	template<class AnyClass> void AddComponent(GameObject& gObj)
	{
		MemoryPool& memPool = MemoryPool::GetInstance();
		Component* addComponent2 = new(memPool.Allocate(sizeof(AnyClass))) AnyClass();

		gObj.componentList.push_back(*addComponent2);
	}

};


#endif // !GAMEOBJECTMANAGER_H
