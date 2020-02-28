#pragma once

#include "../Global_ECS.h"
#include <queue>
#include <array>
#include <map>

class EntityManager
{
public:
	std::map<ENTITY, const char*> _entitiesNameSet;

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

private:
	// We use queue because it is FIFO

	// Queue of available entities
	std::queue<ENTITY> _availableEntities;

	// Number of active entities
	unsigned int _activeEntityCount;

	// Simple array of signatures
	std::array<SIGNATURE, MAX_ENTITIES> _signatures;
};

//#include <queue>								// FIFO storage for entity
//#include <string>								// human-readable name for entity	
//#include <array>								// storage for name 
//#include <vector>								// vector storage for entity_List
//#include "../Global_ECS.h"						// ECS typedefs
//#include "../Systems/System.h"
//
//class EntityManager: public System<EntityManager>
//{
//private:	
//	ENTITYID _activeEntityCount;
//	std::vector<ENTITYID> _activeEntity_List;						//ENTITYID used by game
//	std::queue<ENTITYID> _inactiveEntity_List;						//Recycled ENTITYID that can be used
//
//	std::array<std::string, ENTITY_MAX> _activeEntity_NameList;		//A array of names for quick access vis ENTITYID
//	std::array<SIGNATURE, ENTITY_MAX> _activeEntity_SignatureList;	//A array of entity signature for quick access via ENTITYID
//
//	
//public:
//	EntityManager();
//	virtual void Init();
//	ENTITYID CreateEntity(std::string name = "Unnamed Entity");
//	void EntityDestroyed(ENTITYID entity);
//
//	SIGNATURE GetEntitySignature(ENTITYID entity) const;
//	void SetEntitySignature(ENTITYID entity, SIGNATURE key);
//
//	void GenerateEntityList() const;
//
//	//// Component related funcitons
//	//template<class AnyComp> void AddComponent();
//	//template<class AnyComp> void RemoveComponent();
//};
//
//
//// Some links about template
//	//https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
//	//https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
////Example:GameObjectManager.AddComponent<MeshComponent>(GameObject);