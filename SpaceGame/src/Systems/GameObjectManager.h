#pragma once

#include <vector>								// Dynamic vector array
#include "../Entity/GameObject.h"				// GameObject Class type

class GameObjectManager
{
private:
	static GameObjectManager* instance;						/* Here will be the instance stored. */
	std::vector<std::unique_ptr<GameObject>> gObjList;		// list of global gameobjects - unique pointers to gameobject
	short gObjCount;										// gameObject ID

	GameObjectManager();									/* Private constructor to prevent instancing. */

public:
	//Manager instance functions
	static GameObjectManager& GetInstance();				/* Static access method. */
	static void DestroyInstance();							

	//GameObject Create and Destroy Functions
	GameObject& CreateGameObject(std::string name);	
	void DestroyGameObject(GameObject& target);
	void DestroyGameObject(short id);

	GameObject& GetGameObject(short id);
	void GenerateGameObjectList() const;
	void GenerateComponentList(short index) const;

	template<class AnyComp> 
	void AddComponent(GameObject& gObj);

	template<class AnyComp>
	void RemoveComponent(GameObject& gObj);
};


// Some links about template
	//https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
	//https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
//Example:GameObjectManager.AddComponent<MeshComponent>(GameObject);