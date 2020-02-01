/*********************************************************************************
* \file			Global.cpp
* \author		Chong Jun Yi
* \version		1.0
* \date			30/01/2019
* \par			Engine Code
* \note			Course: GAM150
* \brief		The overall manager for all system in ECS architecture
				- Initalise all system and managers
				- Control flow of system during frame update
				- Clean up all system and manager

* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "Core.h"
#include "GameObjectManager.h"

#include "../Components/MeshComponent.h"

void Core_Init()
{
	//Create all the systems and manager instances
	//MemoryPool::GetInstance();				// Dont use this!
	GameObjectManager::GetInstance();

	GameObject& a = GameObjectManager::GetInstance().CreateGameObject("Hello");
	GameObjectManager::GetInstance().CreateGameObject("World");
	GameObjectManager::GetInstance().CreateGameObject("Hello");
	GameObjectManager::GetInstance().GenerateGameObjectList();

	GameObjectManager::GetInstance().GenerateGameObjectList();
	GameObjectManager::GetInstance().AddComponent<MeshComponent>(a);
	GameObjectManager::GetInstance().AddComponent<MeshComponent>(a);
	GameObjectManager::GetInstance().GenerateComponentList(a._id);
	GameObjectManager::GetInstance().RemoveComponent<MeshComponent>(a);
	GameObjectManager::GetInstance().GenerateComponentList(a._id);
}


void Core_Update()
{
	//Update ECS systems in order

	
}

void Core_Unload()
{
	GameObjectManager::DestroyInstance();
	//MemoryPool::DestroyInstance();				// Dont use this!
}

