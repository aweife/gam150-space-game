#include "Entity.h"
#include "EntityManager.h"

Entity::Entity(std::string name)
{
	// Create an entity with name
	_entityID = EntityManager::GetInstance().CreateEntity(name);

	// Get signature of entity
	_signature = EntityManager::GetInstance().GetEntitySignature(_entityID);
}

