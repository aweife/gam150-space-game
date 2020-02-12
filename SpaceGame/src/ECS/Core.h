#pragma once
#include <memory>
#include "../Managers/ComponentManager.h"
#include "../Managers/EntityManager.h"
#include "../Managers/SystemManager.h"

class Core
{
private:
	std::unique_ptr<ComponentManager> coreComponentManager;
	std::unique_ptr<EntityManager> coreEntityManager;
	std::unique_ptr<SystemManager> coreSystemManager;

public:

	void Core_Init();

	//ENTITY
	ENTITY CreateEntity();
	void EntityDestroyed(ENTITY entity);

	//COMPONENT
	template<typename T>
	void RegisterComponent();

	template<typename T>
	void AddComponent(ENTITY entity, T component);

	template<typename T>
	void RemoveComponent(ENTITY entity);

	template<typename T>
	T& GetComponent(ENTITY entity);

	template<typename T>
	ComponentType GetComponentType();

	template<typename T>
	std::shared_ptr<T> RegisterSystem();

	template<typename T>
	void SetSystemSignature(SIGNATURE signature);
};

static Core coreInstance;

template<typename T>
void Core::RegisterComponent()
{
	coreComponentManager->AddComponent<T>();
}

template<typename T>
void Core::AddComponent(ENTITY entity, T component)
{
	coreComponentManager->AddComponent<T>(entity, component);

	auto signature = coreEntityManager->GetSignature(entity);
	signature.set(coreComponentManager->GetComponentType<T>(), true);
	coreEntityManager->SetSignature(entity, signature);

	coreSystemManager->UpdateEntitySignature(entity, signature);
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