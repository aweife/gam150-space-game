#include "SystemManager.h"
#include "AEEngine.h"
#include "../Systems/RenderSystem.h"

void SystemManager::Init()
{
	// Register systems
	RegisterSystem<RenderSystem>();
}

template<typename T>
std::shared_ptr<T> SystemManager::RegisterSystem()
{
	// Get name of the system
	const char* systemName = typeid(T).name();

	// Assert if the system already exists
	AE_ASSERT(_systemMap.find(systemName) == _systemMap.end() &&
		"Registering system more than once.");

	// Use make_share<T>() to make a shared pointer to the system
	// Using auto because we do not know the type
	auto system = std::make_shared<T>();

	// Insert into system map as a pair: key value -- mapped value
	_systemMap.insert({ systemName, system });

	// Return the shared pointer
	return system;
}

template<typename T>
void SystemManager::SetSignature(SIGNATURE signature)
{
	// Get name of the system
	const char* systemName = typeid(T).name();

	// Assert if the system is used before registering it
	AE_ASSERT(_systemMap.find(systemName) != _systemMap.end() &&
		"Using system before registering.");

	// Insert into signature map as a pair: key value -- mapped value
	_signaturesMap.insert({ systemName, signature });
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
		}
		else
		{
			// Entity signature does not match system signature, erase from set
			system->entitiesList.erase(entity);
		}
	}
}
