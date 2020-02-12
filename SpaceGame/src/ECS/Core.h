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