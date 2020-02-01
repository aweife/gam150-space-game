/*********************************************************************************
* \file			Global.cpp
* \author		Chong Jun Yi
* \version		1.0
* \date			31/01/2019
* \par			Engine Code
* \note			Course: GAM150
* \brief		Manager to handle and store a list of gameobject (entity)
				- Create and Remove GameObject
				-

* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "GameObjectManager.h"
#include <string>
#include <algorithm>
#include "../Tools/Console.h"
#include "../Components/MeshComponent.h"

// Null value set before execution of program
// Instance will be created on demand.
GameObjectManager* GameObjectManager::instance = nullptr;

/******************************************************************************/
/*!
  \brief	Get singleton instance
*/
/******************************************************************************/
GameObjectManager& GameObjectManager::GetInstance()
{
	if (instance == 0)
	{
		instance = new GameObjectManager();
	}

	AE_ASSERT(instance);	//Assert if fail to create GameManager
	return *instance;
}

/******************************************************************************/
/*!
  \brief	Destroy singleton instance
*/
/******************************************************************************/
void GameObjectManager::DestroyInstance()
{	
	//Unique pointer will clean up itself
	instance->gObjList.clear();
	// Delete singleton instance
	delete(instance);
}

/******************************************************************************/
/*!
  \brief	Constructor and initalise data members
*/
/******************************************************************************/
GameObjectManager::GameObjectManager() :gObjCount{ 0 }
{
}

/******************************************************************************/
/*!
  \brief	Create a new empty gameobject and store in list
  \note		To Do: There are holes due to removed ID... can we reuse them
*/
/******************************************************************************/
GameObject& GameObjectManager::CreateGameObject(std::string name)
{
	GameObject* newGObj = new GameObject(name, gObjCount);			//Create GameObject on heap
	gObjList.push_back(std::unique_ptr<GameObject>{newGObj});		//Pass to unique pointer so that it will dispose when out of scope 

	gObjCount++;
	return *newGObj;

}

/******************************************************************************/
/*!
  \brief	Destroy a new empty gameobject by reference's id
  \note		To Do: There are holes due to removed ID... can we reuse them
*/
/******************************************************************************/
void GameObjectManager::DestroyGameObject(GameObject& target)
{
	short targetid = target._id;
	for (auto i = gObjList.begin(); i != gObjList.end(); ++i)
	{
		if ((*i)->_id == targetid)
		{
			gObjList.erase(i);
			break;
		}
	}
}

/******************************************************************************/
/*!
  \brief	Destroy a new empty gameobject by id
*/
/******************************************************************************/
void GameObjectManager::DestroyGameObject(short id)
{
	for (auto i = gObjList.begin(); i != gObjList.end(); ++i)
	{
		if ((*i)->_id == id)
		{
			gObjList.erase(i);
			break;
		}
	}
}

/******************************************************************************/
/*!
  \brief	Return a GameObject reference by id
*/
/******************************************************************************/
GameObject& GameObjectManager::GetGameObject(short id)
{
	return *gObjList.at(id);
}

/******************************************************************************/
/*!
  \brief	Debug function to display list of gameobjects
*/
/******************************************************************************/
void GameObjectManager::GenerateGameObjectList() const
{
	if (gObjList.empty()) return;

	Console_Cout("---Generating GameObject List---");
	for (auto& i : gObjList )
	{
		Console_Cout(i->_name);
	}
}

/******************************************************************************/
/*!
  \brief	Debug function to display list of components in gameobject
*/
/******************************************************************************/
void GameObjectManager::GenerateComponentList(short index) const
{
	if (gObjList.empty()) return;

	const GameObject& target = *gObjList.at(index);

	//Debug Information
	Console_Cout("---Generating Internal Component ---");
	Console_Cout("GameObject: " + target._name, (int)index);
	if (target.componentList.empty()) Console_Cout("No Components Found!");

	for (auto& i : target.componentList)//range based loop
	{
		Console_Cout(i->_name);
	}
}



/******************************************************************************/
/*!
  \brief	Add any type of derived component class into the gameobject
*/
/******************************************************************************/
template<class AnyComp>
void GameObjectManager::AddComponent(GameObject& gObj)
{
	#pragma region Broken MemoryPool Implementation
		// -- There are some leaks in memory pool -- so implementation not used --
		//MemoryPool& memPool = MemoryPool::GetInstance();
		//Component* addComponent2 = new(memPool.Allocate(sizeof(AnyClass))) AnyClass();
	#pragma endregion

	gObj.AddComponent<AnyComp>();		//Call function from GameObject Class
}
//explict template instances
template void GameObjectManager::AddComponent<MeshComponent>(GameObject& gObj);

/******************************************************************************/
/*!
  \brief	Add any type of derived component class into the gameobject
*/
/******************************************************************************/
template<class AnyComp>
void GameObjectManager::RemoveComponent(GameObject& gObj)
{
	gObj.RemoveComponent<AnyComp>();		//Call function from GameObject Class
}
//explict template instances
template void GameObjectManager::RemoveComponent<MeshComponent>(GameObject& gObj);