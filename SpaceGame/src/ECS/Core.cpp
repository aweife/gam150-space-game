/*********************************************************************************
* \file			Core.cpp
* \brief		Abstract class for a generic component storage
* \author		Jun Yi, Chong, 100% Code Contribution
*
*				Overall Manager for ECS
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "Core.h"								//Self Header
#include "Factory.h"
#include "../Managers/CameraManager.h"			//Late Update
#include "../Tools/Console.h"

void Core::Core_Init()
{
	//Create the 3 main manager instances
	coreComponentManager = std::make_unique<ComponentManager>();
	coreEntityManager = std::make_unique<EntityManager>();
	coreSystemManager = std::make_unique<SystemManager>();

	// Register components and systems
	coreComponentManager->Init();
	coreSystemManager->Init();
}

void Core::Core_Unload()
{
	coreComponentManager->RemoveAllComponent(); //release memory
}
void Core::Core_Update()
{
	// Update systems
	coreSystemManager->Update();

	// Late Update
	CameraManager::Update();
}

void Core::Core_Render()
{
	// Update systems
	
	coreSystemManager->Render();
}

ENTITY Core::CreateEntity(const char* name)
{
	return coreEntityManager->CreateEntity(name);
}

void Core::EntityDestroyed(ENTITY entity)
{
	//The original order is entity -> component -> system
	coreEntityManager->EntityDestroyed(entity);
	
	coreSystemManager->EntityDestroyed(entity); // Some system will perform functions on component when a object is destroyed

	coreComponentManager->EntityDestroyed(entity);
}

void Core::DestroyAllEntity()
{
	//Loop through a copy 
	while(coreEntityManager->GetActiveSet().size() > 0)
	{
		EntityDestroyed(*coreEntityManager->GetActiveSet().begin());
	}
}

//Purely used for debuging
void Core::GenerateWorldState()
{
	Console_Cout("---Generating World State---");
	
	Console_Newline();
}
