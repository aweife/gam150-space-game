#include "EntityManager.h"
#include "../Systems/ComponentManager.h"

#include "../Tools/Console.h"				//REMOVE AFTER TESTING

EntityManager::EntityManager() 
{
	_activeEntityCount = 0;
}

void EntityManager::Init()
{
}

ENTITYID EntityManager::CreateEntity(std::string name)
{
	AE_ASSERT(_activeEntityCount < ENTITY_MAX && "Too many entities");

	ENTITYID id = _activeEntityCount; //Assign an ID based on nth exisiting entity

	//Recycle an ENTITY ID, First in First out
	if (!_inactiveEntity_List.empty())
	{
		id = _inactiveEntity_List.front();
		_inactiveEntity_List.pop();
	}
	//'Creating' the new entity 
	_activeEntity_List.push_back(id);		//Add the new entity to active vector
	_activeEntity_NameList[id] = name;		//Store name in a accessable array
	++_activeEntityCount;					//Increament number of exisiting entity

	return id;
}

void EntityManager::DestroyEntity(ENTITYID entity)
{
	AE_ASSERT(entity < ENTITY_MAX && "Entity out of range.");

	// Reset the component signature since entity will be destroyed
	_activeEntity_SignatureList[entity].reset();

	// Put the destroyed ID into inactive queue to be recycled
	_inactiveEntity_List.push(entity);

	// Remove from active vector
	for (auto i = _activeEntity_List.begin(); i != _activeEntity_List.end(); ++i)
	{
		if (*i == entity)
		{
			_activeEntity_List.erase(i);
			break;
		}
	}
	--_activeEntityCount;					//Decreament number of exisiting entity

	//Remove all components in that entity
	ComponentManager::GetInstance().EntityDestroyed(entity);
}

SIGNATURE EntityManager::GetEntitySignature(ENTITYID entity) const
{
	AE_ASSERT(entity < ENTITY_MAX && "Entity out of range.");

	return _activeEntity_SignatureList[entity];		//Informs what components the entity contain
}

void EntityManager::SetEntitySignature(ENTITYID entity, SIGNATURE key)
{
	AE_ASSERT(entity < ENTITY_MAX && "Entity out of range.");

	_activeEntity_SignatureList[entity] = key;		//Add or remove components the entity contain
}

void EntityManager::GenerateEntityList() const
{
	if (_activeEntity_List.empty()) return;

	Console_Cout("---Generating Entity List---");
	for (auto i : _activeEntity_List)
	{
		Console_Cout(_activeEntity_NameList[i], i);		//Format: Name EntityID
	}
	Console_Newline();
}









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