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
	static GameObjectManager* GetInstance();
	static void DestroyInstance();
	void CreateGameObject(std::string name);
	void GenerateGameObjectList() const;
	void GenerateComponentList(short index) const;
	void AddComponent(GameObject& gObj, const Component& addComponent);

};

#endif // !GAMEOBJECTMANAGER_H
