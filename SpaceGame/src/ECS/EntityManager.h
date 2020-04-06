/*********************************************************************************
* \file			EntityManager.h
* \brief		Manager for entities in the game
* \author		Jun Yi, Chong, 50% Code Contribution
*        		Wei Feng, Ang, 50% Code Contribution
*
*				Responsible for creating and destroying entities in the game. Also
*				keep tracks of their signatures.
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "../Global_ECS.h"							// ECS typedefs
#include <map>
#include <queue>
#include <array>
#include <set>

class EntityManager
{
public:
	// Constructor
	// Initialise a queue of inactive/available entities with unique id
	EntityManager();

	// Requests an entity - this removes the entity from the front of the queue
	ENTITY CreateEntity(const char* name = "");

	// Return an entity to the back of the queue
	void EntityDestroyed(ENTITY entity);

	// Assign a signature to an entity
	void SetSignature(ENTITY entity, SIGNATURE signature);

	// Returns the signature of an entity
	SIGNATURE GetSignature(ENTITY entity);

	// Returns a COPY of the active Entity Set
	const std::set<ENTITY> GetActiveSet() const;
	void ClearActiveSet();

	unsigned int GetActiveCount();

private:
	// Map the entity to a human readable name
	std::map<ENTITY, const char*> _entitiesNameSet;

	// We use queue because it is FIFO
	// Queue of available entities
	std::queue<ENTITY> _availableEntities;

	// Number of active entities
	unsigned int _activeEntityCount;
	std::set<ENTITY> _activeEntity;

	// Simple array of signatures ... "contains gaps"...
	std::array<SIGNATURE, MAX_ENTITIES> _signatures;
};

//public:
//	void GenerateEntityList() const;
//
//// Some links about template
//	//https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
//	//https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
////Example:GameObjectManager.AddComponent<MeshComponent>(GameObject);