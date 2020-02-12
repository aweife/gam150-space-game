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
	void Core_Update();

	//ENTITY
	ENTITY CreateEntity();
	void EntityDestroyed(ENTITY entity);

	//COMPONENT
	template<typename T>
	void RegisterComponent()
	{
		coreComponentManager->AddComponent<T>();
	}

	template<typename T>
	void AddComponent(ENTITY entity, T* component)
	{
		coreComponentManager->AddComponent<T>(entity, component);

		auto signature = coreEntityManager->GetSignature(entity);
		signature.set(coreComponentManager->GetComponentType<T>(), true);
		coreEntityManager->SetSignature(entity, signature);

		coreSystemManager->UpdateEntitySignature(entity, signature);
	}

	template<typename T>
	void RemoveComponent(ENTITY entity)
	{
		coreComponentManager->RemoveComponent<T>(entity);

		auto signature = coreEntityManager->GetSignature(entity);
		signature.set(coreComponentManager->GetComponentType<T>(), false);
		coreEntityManager->SetSignature(entity, signature);

		coreSystemManager->UpdateEntitySignature(entity, signature);
	}

	template<typename T>
	T* GetComponent(ENTITY entity)
	{
		return coreComponentManager->GetComponent<T>(entity);
	}


	template<typename T>
	ComponentType GetComponentType()
	{
		return coreComponentManager->GetComponentType<T>();
	}

	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return coreSystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(SIGNATURE signature)
	{
		coreSystemManager->SetSignature<T>(signature);
	}
};
