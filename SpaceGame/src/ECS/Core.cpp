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
#include "Core.h"

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

void Core::DestroyEntity(ENTITY entity)
{
	coreEntityManager->DestroyEntity(entity);

	coreComponentManager->EntityDestroyed(entity);

	coreSystemManager->EntityDestroyed(entity);
}

template<typename T>
void Core::RegisterComponent()
{
	mComponentManager->RegisterComponent<T>();
}

template<typename T>
void Core::AddComponent(ENTITY entity, T component)
{
	mComponentManager->AddComponent<T>(entity, component);

	auto signature = mEntityManager->GetSignature(entity);
	signature.set(mComponentManager->GetComponentType<T>(), true);
	mEntityManager->SetSignature(entity, signature);

	mSystemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
void Core::RemoveComponent(ENTITY entity)
{
	mComponentManager->RemoveComponent<T>(entity);

	auto signature = mEntityManager->GetSignature(entity);
	signature.set(mComponentManager->GetComponentType<T>(), false);
	mEntityManager->SetSignature(entity, signature);

	mSystemManager->EntitySignatureChanged(entity, signature);
}

template<typename T>
T& Core::GetComponent(ENTITY entity)
{
	return mComponentManager->GetComponent<T>(entity);
}

template<typename T>
ComponentType Core::GetComponentType()
{
	return mComponentManager->GetComponentType<T>();
}

template<typename T>
std::shared_ptr<T> Core::RegisterSystem()
{
	return mSystemManager->RegisterSystem<T>();
}

template<typename T>
void Core::SetSystemSignature(SIGNATURE signature)
{
	mSystemManager->SetSignature<T>(signature);
}



void Core_Update()
{
	//Update ECS systems in order

	//Change this to input-update-render sequence
	//SpriteManager::GetInstance().Update();
	
}

void Core_Unload()
{
	/*SpriteManager::DestroyInstance();
	ComponentManager::DestroyInstance();
	EntityManager::DestroyInstance();*/
}

