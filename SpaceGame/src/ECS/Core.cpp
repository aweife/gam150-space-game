/*********************************************************************************
* \file			Core.cpp
* \author		Chong Jun Yi
* \version		1.0
* \date			30/01/2019
* \par			Engine Code
* \note			Course: GAM150
* \brief		The overall manager for 3 main managers in ECS architecture
				- Initalise all system and managers
				- Control ???
				- Clean up all system and manager

* \copyright	Copyright (c) 2019 DigiPen Institute of Technology. Reproduction
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

