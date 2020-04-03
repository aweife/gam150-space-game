/*********************************************************************************
* \file			EntityManager.cpp
* \brief		Manager for entities in the game
* \author		Chong Jun Yi, 50% Code Contribution
* \author		Ang Wei Feng, 50% Code Contribution
*
*				Responsible for creating and destroying entities in the game. Also
*				keep tracks of their signatures.
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "EntityManager.h"
#include "AEEngine.h"

EntityManager::EntityManager() : _activeEntityCount{ 0 }
{
	// Add to the queue with all possible ids
	for (ENTITY entity = 1; entity < MAX_ENTITIES; ++entity)
		_availableEntities.push(entity);
}

ENTITY EntityManager::CreateEntity(const char* name)
{
	UNREFERENCED_PARAMETER(name);
	

	if(_activeEntityCount > MAX_ENTITIES)
	{
		printf("TOO MANY ENTITY %ui", _activeEntityCount);
	}
	// Assert if we reached the cap
	AE_ASSERT(_activeEntityCount < MAX_ENTITIES && "Too many entities created");
	
	// Take from the front of the queue
	ENTITY entity = _availableEntities.front();
	//_entitiesNameSet.insert(std::pair<)
	//_entitiesNames[entity] = name;
	_availableEntities.pop();
	++_activeEntityCount;
	_activeEntity.insert(entity);

	return entity;
}

void EntityManager::EntityDestroyed(ENTITY entity)
{
	// Assert if given entity is invalid
	AE_ASSERT(entity < MAX_ENTITIES && "Entity is out of range.");

	// Reset signature of entity
	_signatures[entity].reset();

	// Add to the back of the queue
	_availableEntities.push(entity);
	_activeEntity.erase(entity);
	--_activeEntityCount;
}

void EntityManager::SetSignature(ENTITY entity, SIGNATURE key)
{
	// Assert if given entity is invalid
	AE_ASSERT(entity < MAX_ENTITIES && "Entity is out of range.");

	// Save this entity's signature to our array
	_signatures[entity] = key;
}

SIGNATURE EntityManager::GetSignature(ENTITY entity)
{
	// Assert if given entity is invalid
	AE_ASSERT(entity <= MAX_ENTITIES && "Entity is out of range.");

	return _signatures[entity];
}

const std::set<ENTITY> EntityManager::GetActiveSet() const
{
	return _activeEntity;
}

void EntityManager::ClearActiveSet()
{
	_activeEntity.clear();
}

unsigned int EntityManager::GetActiveCount()
{
	return _activeEntityCount;
}