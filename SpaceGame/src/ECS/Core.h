#pragma once
#include <memory>
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "../Tools/MemoryLeak.h"
class Core
{
public:
	// Singleton pattern
	static Core& Get()
	{
		static Core instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}
	Core(Core const&) = delete;
	void operator=(Core const&) = delete;

	// Core functions
	void Core_Init();
	void Core_Update();
	void Core_Render();
	void Core_Unload();

	// ENTITY
	ENTITY CreateEntity(const char* name = "");
	void EntityDestroyed(ENTITY entity);

	// COMPONENT
	template<typename T>
	void RegisterComponent()
	{
		coreComponentManager->AddComponent<T>();
	}

	// Setting the signature for entity
	template<typename T>
	void AddComponent(ENTITY entity, T* component)
	{
		coreComponentManager->AddComponent<T>(entity, component);
		
		auto old_signature = coreEntityManager->GetSignature(entity);
		auto signature = coreEntityManager->GetSignature(entity);
		signature.set(coreComponentManager->GetComponentType<T>(), true);
		coreEntityManager->SetSignature(entity, signature);

		coreSystemManager->UpdateEntitySignature(entity, signature);

		// Update base component
		component->_entityParent = entity;
	}

	template<typename T>
	void RemoveComponent(ENTITY entity)
	{
		coreComponentManager->RemoveComponent<T>(entity);

		auto old_signature = coreEntityManager->GetSignature(entity);
		auto signature = coreEntityManager->GetSignature(entity);
		signature.set(coreComponentManager->GetComponentType<T>(), false);
		coreEntityManager->SetSignature(entity, signature);

		coreSystemManager->UpdateEntitySignature(entity, signature, old_signature);
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
	std::shared_ptr<System> GetSystem()
	{
		return coreSystemManager->GetSystemInstance<T>();
	}

	template<typename T>
	void SetSystemSignature(SIGNATURE signature)
	{
		coreSystemManager->SetSignature<T>(signature);
	}

	void GenerateWorldState();
private:
	// Singleton pattern
	Core() {}                    // Constructor. The {} brackets are needed here

	// Pointers to managers
	std::unique_ptr<ComponentManager> coreComponentManager;
	std::unique_ptr<EntityManager> coreEntityManager;
	std::unique_ptr<SystemManager> coreSystemManager;
};
