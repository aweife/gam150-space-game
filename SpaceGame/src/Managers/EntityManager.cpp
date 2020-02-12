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

void EntityManager::SetSignature(Entity entity, Signature signature)
{
	// Assert if given entity is invalid
	AE_ASSERT(entity < MAX_ENTITIES && "Entity is out of range.");

	// Save this entity's signature to our array
	_signatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity)
{
	// Assert if given entity is invalid
	AE_ASSERT(entity < MAX_ENTITIES && "Entity is out of range.");

	return _signatures[entity];
}

//#include "../Systems/ComponentManager.h"
//
//#include "../Tools/Console.h"				//REMOVE AFTER TESTING
//
//EntityManager::EntityManager() 
//{
//	_activeEntityCount = 0;
//}
//
//void EntityManager::Init()
//{
//}
//
//ENTITYID EntityManager::CreateEntity(std::string name)
//{
//	AE_ASSERT(_activeEntityCount < ENTITY_MAX && "Too many entities");
//
//	ENTITYID id = _activeEntityCount; //Assign an ID based on nth exisiting entity
//
//	//Recycle an ENTITY ID, First in First out
//	if (!_inactiveEntity_List.empty())
//	{
//		id = _inactiveEntity_List.front();
//		_inactiveEntity_List.pop();
//	}
//	//'Creating' the new entity 
//	_activeEntity_List.push_back(id);		//Add the new entity to active vector
//	_activeEntity_NameList[id] = name;		//Store name in a accessable array
//	++_activeEntityCount;					//Increament number of exisiting entity
//
//	return id;
//}
//
//void EntityManager::DestroyEntity(ENTITYID entity)
//{
//	AE_ASSERT(entity < ENTITY_MAX && "Entity out of range.");
//
//	// Reset the component signature since entity will be destroyed
//	_activeEntity_SignatureList[entity].reset();
//
//	// Put the destroyed ID into inactive queue to be recycled
//	_inactiveEntity_List.push(entity);
//
//	// Remove from active vector
//	for (auto i = _activeEntity_List.begin(); i != _activeEntity_List.end(); ++i)
//	{
//		if (*i == entity)
//		{
//			_activeEntity_List.erase(i);
//			break;
//		}
//	}
//	--_activeEntityCount;					//Decreament number of exisiting entity
//
//	//Remove all components in that entity
//	ComponentManager::GetInstance().EntityDestroyed(entity);
//}
//
//SIGNATURE EntityManager::GetEntitySignature(ENTITYID entity) const
//{
//	AE_ASSERT(entity < ENTITY_MAX && "Entity out of range.");
//
//	return _activeEntity_SignatureList[entity];		//Informs what components the entity contain
//}
//
//void EntityManager::SetEntitySignature(ENTITYID entity, SIGNATURE key)
//{
//	AE_ASSERT(entity < ENTITY_MAX && "Entity out of range.");
//
//	_activeEntity_SignatureList[entity] = key;		//Add or remove components the entity contain
//}
//
//void EntityManager::GenerateEntityList() const
//{
//	if (_activeEntity_List.empty()) return;
//
//	Console_Cout("---Generating Entity List---");
//	for (auto i : _activeEntity_List)
//	{
//		Console_Cout(_activeEntity_NameList[i], i);		//Format: Name EntityID
//	}
//	Console_Newline();
//}









//template<class AnyComp>
//void GameObject::AddComponent()
//{
//	Component* newComponent = new AnyComp();	
//	componentList.push_back(std::unique_ptr<Component>{newComponent});
//}
////explict template instances
//template void GameObject::AddComponent<MeshComponent>();
//
//template<class AnyComp>
//void GameObject::RemoveComponent()
//{
//	for (auto i = componentList.begin(); i != componentList.end(); ++i)
//	{
//		if ((*i)->_name.compare(typeid(AnyComp).name()) == 0)
//		{
//			componentList.erase(i);
//			break;
//		}
//	}
//}
////explict template instances
//template void GameObject::RemoveComponent<MeshComponent>();