#include "SystemManager.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/PhysicsSystem.h"
#include "../Systems/CollisionSystem.h"

void SystemManager::Init()
{
	// Register systems
	RegisterSystem<RenderSystem>();
	RegisterSystem<PhysicsSystem>();
	RegisterSystem<CollisionSystem>();


	for (auto const& system : _systemMap)
	{
		system.second->Init();
	}
}

void SystemManager::Update()
{
	for (auto const& system : _systemMap)
	{
		system.second->Update();
	}
}

void SystemManager::Render()
{
	for (auto const& system : _systemMap)
	{
		system.second->Render();
	}
}

void SystemManager::EntityDestroyed(ENTITY entity)
{
	// Erase an entity from all system lists
	for (auto const& pair : _systemMap)
	{
		// The first of the pair is the system name
		// The second of the pair is the shared pointer to the system
		pair.second->entitiesList.erase(entity);
	}
}

void SystemManager::UpdateEntitySignature(ENTITY entity, SIGNATURE entitySignature)
{
	for (auto const& pair : _systemMap)
	{
		// The first of the pair is the system name
		// The second of the pair is the shared pointer to the system
		auto const& name = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = _signaturesMap[name];

		// Do bitwise comparison of the signatures
		// The & operator returns a result for us to compare against
		// 01001101 & 00001100 = 00001100
		// 01000101 & 00001100 = 00000100 (Wrong entity)
		if ((entitySignature & systemSignature) == systemSignature)
		{
			// Entity signature matches system signature, add into set
			system->entitiesList.insert(entity);
			system->OnComponentAdd(entity);
		}
		else
		{
			// Entity signature does not match system signature, erase from set
			// Will run erase on all systems 
			system->OnComponentRemove(entity);
			system->entitiesList.erase(entity);
		}
	}
}
