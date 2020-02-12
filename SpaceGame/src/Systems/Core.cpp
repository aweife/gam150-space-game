/*********************************************************************************
* \file			Core.cpp
* \author		Chong Jun Yi
* \version		1.0
* \date			30/01/2020
* \par			Engine Code
* \note			Course: GAM150
* \brief		The overall manager for all system in ECS architecture
				- Initalise all system and managers
				- Control flow of system during frame update
				- Clean up all system and manager

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "Core.h"
#include "System.h"
#include "../Entity/EntityManager.h"
#include "ComponentManager.h"
#include "SpriteManager.h"

#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
void Core_Init()
{
	//Create all the systems and manager instances
	EntityManager::GetInstance().Init();
	ComponentManager::GetInstance().Init();
	SpriteManager::GetInstance().Init();

	ENTITYID number0 = EntityManager::GetInstance().CreateEntity("Hello");								//Entity 0
	EntityManager::GetInstance().GenerateEntityList();

	/*EntityManager::GetInstance().DestroyEntity(number0);
	EntityManager::GetInstance().GenerateEntityList();*/
	//ComponentManager::GetInstance().RemoveComponent<SpriteComponent>(1);
	
	ComponentManager::GetInstance().AddComponent<SpriteComponent>(0, new SpriteComponent(1));
	ComponentManager::GetInstance().AddComponent<TransformComponent>(0, new TransformComponent(1));
	ComponentManager::GetInstance().GenerateComponentCollection();

	// Add transform
	
}

void Core_Update()
{
	//Update ECS systems in order

	//Change this to input-update-render sequence
	SpriteManager::GetInstance().Update();

	TransformComponent* thisTransform = ComponentManager::GetInstance().GetComponent<TransformComponent>(0);
	thisTransform->position.x += 2;

	// UPDATE PHYSICS HERE
	
}

void Core_Unload()
{
	SpriteManager::DestroyInstance();
	ComponentManager::DestroyInstance();
	EntityManager::DestroyInstance();
}

