#include "EntityManager.h"
#include "ComponentManager.h"
#include "AEEngine.h"

#include "../Tools/Console.h"				//REMOVE AFTER TESTING

EntityManager::EntityManager() 
{
	_activeEntityCount = 0;
}

ENTITY EntityManager::CreateEntity(const char* name)
{
	AE_ASSERT(_activeEntityCount < MAX_ENTITIES && "Too many entities");

	ENTITY id = _activeEntityCount; //Assign an ID based on nth exisiting entity

	//Recycle an ENTITY ID, First in First out
	//if (!_inactiveEntity_List.empty())
	//{
	//	id = _inactiveEntity_List.front();
	//	_inactiveEntity_List.pop();
	//}
	//'Creating' the new entity 
	_availableEntities.push(id);		//Add the new entity to active vector
	//_activeEntity_NameList[id] = name;		//Store name in a accessable array
	++_activeEntityCount;					//Increament number of exisiting entity

	return id;
}

void EntityManager::DestroyEntity(ENTITY entity)
{
	AE_ASSERT(entity < MAX_ENTITIES && "Entity out of range.");

	// Reset the component signature since entity will be destroyed
	_signatures[entity].reset();

	// Put the destroyed ID into inactive queue to be recycled
	//_inactiveEntity_List.push(entity);

	// Remove from active vector
	for (auto i = _availableEntities.begin(); i != _activeEntity_List.end(); ++i)
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

SIGNATURE EntityManager::GetEntitySignature(ENTITY entity) const
{
	AE_ASSERT(entity < ENTITY_MAX && "Entity out of range.");

	return _activeEntity_SignatureList[entity];		//Informs what components the entity contain
}

void EntityManager::SetEntitySignature(ENTITY entity, SIGNATURE key)
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