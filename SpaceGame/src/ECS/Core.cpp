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
#include "Core.h"			//Self Header

void Core::Core_Init()
{
	//Create the 3 main manager instances
	coreComponentManager = std::make_unique<ComponentManager>();
	coreEntityManager = std::make_unique<EntityManager>();
	coreSystemManager = std::make_unique<SystemManager>();
}

ENTITY Core::CreateEntity()
{
	return coreEntityManager->CreateEntity();
}

void Core::EntityDestroyed(ENTITY entity)
{
	coreEntityManager->EntityDestroyed(entity);

	coreComponentManager->EntityDestroyed(entity);

	coreSystemManager->EntityDestroyed(entity); //Will we need this
}

template<typename T>
void Core::RegisterComponent()
{
	coreComponentManager->AddComponent<T>();
}

template<typename T>
void Core::RemoveComponent(ENTITY entity)
{
	coreComponentManager->RemoveComponent<T>(entity);

	auto signature = coreEntityManager->GetSignature(entity);
	signature.set(coreComponentManager->GetComponentType<T>(), false);
	coreEntityManager->SetSignature(entity, signature);

	coreSystemManager->UpdateEntitySignature(entity, signature);
}

template<typename T>
T& Core::GetComponent(ENTITY entity)
{
	return coreComponentManager->GetComponent<T>(entity);
}

template<typename T>
ComponentType Core::GetComponentType()
{
	return coreComponentManager->GetComponentType<T>();
}

template<typename T>
std::shared_ptr<T> Core::RegisterSystem()
{
	return coreSystemManager->RegisterSystem<T>();
}

template<typename T>
void Core::SetSystemSignature(SIGNATURE signature)
{
	coreSystemManager->SetSignature<T>(signature);
}

