#pragma once

#include <memory>
#include <unordered_map>
#include "../Global_ECS.h"
#include "AEEngine.h"
#include "../Systems/System.h"

class SystemManager
{
public:
	void Init();
	// Shared pointers use reference counting - it is active as long as there
	// is at least one referencing it
	// We can create a pointer to the registered system and return it to core.

	void Update();
	void Render();

	// Returns a shared pointer to this system
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
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

	// Sets the unique signature for this system
	// The template is needed to get the name of the system
	template<typename T>
	void SetSignature(SIGNATURE signature)
	{
		// Get name of the system
		const char* systemName = typeid(T).name();

		// Assert if the system is used before registering it
		AE_ASSERT(_systemMap.find(systemName) != _systemMap.end() &&
			"Using system before registering.");

		// Insert into signature map as a pair: key value -- mapped value
		_signaturesMap.insert({ systemName, signature });
	}

	// Erase an entity from all systems' entitiesList
	void EntityDestroyed(ENTITY entity);

	// Notify all systems an entity changed signature (add/remove component)
	void UpdateEntitySignature(ENTITY entity, SIGNATURE entitySignature);

private:
	// Map stores elements in pairs: A key value and a mapped value
	// The key value (.first) can be used to uniquely identify the mapped 
	// value (.second)
	// We use unordered map because it uses a hash table, which is O(1) speed

	// Map from string to a signature
	std::unordered_map<const char*, SIGNATURE> _signaturesMap;

	// Map from string to a system pointer
	std::unordered_map<const char*, std::shared_ptr<System>> _systemMap;
};