#include "EntityManager.h"
#include "AEEngine.h"

EntityManager::EntityManager()
{
	// Add to the queue with all possible ids
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		_availableEntities.push(entity);
}

Entity EntityManager::CreateEntity()
{
	// Assert if we reached the cap
	AE_ASSERT(_activeEntityCount < MAX_ENTITIES && "Too many entities created.");

	// Take from the front of the queue
	Entity entity = _availableEntities.front();
	_availableEntities.pop();
	++_activeEntityCount;

	return entity;
}

void EntityManager::DestroyEntity(Entity entity)
{
	// Assert if given entity is invalid
	AE_ASSERT(entity < MAX_ENTITIES && "Entity is out of range.");

	// Reset signature of entity
	_signatures[entity].reset();

	// Add to the back of the queue
	_availableEntities.push(entity);
	--_activeEntityCount;
}

void EntityManager::SetEntitySignature(ENTITY entity, SIGNATURE key)
{
	// Assert if given entity is invalid
	AE_ASSERT(entity < MAX_ENTITIES && "Entity is out of range.");

	// Save this entity's signature to our array
	_signatures[entity] = key;
}

Signature EntityManager::GetSignature(Entity entity)
{
	// Assert if given entity is invalid
	AE_ASSERT(entity < MAX_ENTITIES && "Entity is out of range.");

	return _signatures[entity];
}
