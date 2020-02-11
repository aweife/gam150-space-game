#pragma once
#include <queue>								// FIFO storage for entity
#include <string>								// human-readable name for entity	
#include <array>								// storage for name 
#include <vector>								// vector storage for entity_List
#include "../Global_ECS.h"						// ECS typedefs
#include "../Systems/System.h"

class EntityManager: public System<EntityManager>
{
private:	
	ENTITYID _activeEntityCount;
	std::vector<ENTITYID> _activeEntity_List;						//ENTITYID used by game
	std::queue<ENTITYID> _inactiveEntity_List;						//Recycled ENTITYID that can be used

	std::array<std::string, ENTITY_MAX> _activeEntity_NameList;		//A array of names for quick access vis ENTITYID
	std::array<SIGNATURE, ENTITY_MAX> _activeEntity_SignatureList;	//A array of entity signature for quick access via ENTITYID

	
public:
	EntityManager();
	virtual void Init();
	ENTITYID CreateEntity(std::string name = "Unnamed Entity");
	void DestroyEntity(ENTITYID entity);

	SIGNATURE GetEntitySignature(ENTITYID entity) const;
	void SetEntitySignature(ENTITYID entity, SIGNATURE key);

	void GenerateEntityList() const;

	//// Component related funcitons
	//template<class AnyComp> void AddComponent();
	//template<class AnyComp> void RemoveComponent();
};


// Some links about template
	//https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
	//https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
//Example:GameObjectManager.AddComponent<MeshComponent>(GameObject);