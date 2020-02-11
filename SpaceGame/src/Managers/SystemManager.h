#pragma once

#include <memory>
#include <unordered_map>
#include "../Global_ECS.h"
#include "../Systems/System.h"

class SystemManager
{
public:
	// Shared pointers use reference counting - it is active as long as there
	// is at least one referencing it
	// We can create a pointer to the registered system and return it to core.

	// Returns a shared pointer to this system
	template<typename T>
	std::shared_ptr<T> RegisterSystem();

	// Sets the unique signature for this system
	template<typename T>
	void SetSignature(Signature signature);

	// Erase an entity from all systems' entitiesList
	void DestroyEntity(Entity entity);

	// Notify all systems an entity changed signature (add/remove component)
	void UpdateEntitySignature(Entity entity, Signature signature);

private:
	// Map stores elements in pairs: A key value and a mapped value
	// The key value (.first) can be used to uniquely identify the mapped 
	// value (.second)
	// We use unordered map because it uses a hash table, which is O(1) speed

	// Map from string to a signature
	std::unordered_map<const char*, Signature> _Signatures;

	// Map from string to a system pointer
	std::unordered_map<const char*, std::shared_ptr<System>> _Systems;
};