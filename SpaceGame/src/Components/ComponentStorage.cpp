#include "ComponentStorage.h"	//Self Header
#include "ComponentList.h"		//Header to all types of component used in game

/******************************************************************************/
/*!
  \brief	Adds a component to its respective component storage, 
            called by ComponentManager
*/
/******************************************************************************/
template<typename T>
void ComponentStorage<T>::RegisterComponent(ENTITY entity, T* component)
{
	AE_ASSERT(componentArray.find(entity) == componentArray.end());		//Component already exists

	//Update the index-entity relation map
	entityToIndexMap[entity] = currSize;
	indexToEntityMap[currSize] = entity;

	//Register the component into storage
	componentArray.insert({entity, std::unique_ptr<T>{component}});
}
template void ComponentStorage<cSprite>::RegisterComponent(ENTITY entity, cSprite* component);

/******************************************************************************/
/*!
  \brief	Remove a component to its respective component storage,
			called by ComponentManager
*/
/******************************************************************************/
template<typename T>
void ComponentStorage<T>::UnregisterComponent(ENTITY entity)
{
	AE_ASSERT(componentArray.find(entity) != componentArray.end());		//Component already does not exist
	
	unsigned int unregisterIndex = entityToIndexMap[entity];
	//Move the last element into the deleted component space...so that update will run without any gaps
	unsigned int backComponentIndex = currSize - 1;
	componentArray[unregisterIndex] = componentArray[backComponentIndex];

	//Update the index-entity relation map for the last element that has been moved
	ENTITY backEntity = entityToIndexMap[backComponentIndex];
	entityToIndexMap[backEntity] = unregisterIndex;
	indexToEntityMap[unregisterIndex] = backEntity;

	//Remove deleted component 
	entityToIndexMap.erase(entity);
	indexToEntityMap.erase(backComponentIndex);
}
template void ComponentStorage<cSprite>::UnregisterComponent(ENTITY entity);

/******************************************************************************/
/*!
  \brief	Returns a component to its that belong to an entity,
	        Return nullptr if no such component found to that entity
			called by ComponentManager
*/
/******************************************************************************/
template<typename T>
T* ComponentStorage<T>::RetrieveComponent(ENTITY entity)
{
	if (entityToIndexMap.find(entity) != componentArray.end()) //Check if the component exists in the array
	{
		return componentArray[entityToIndexMap.find(entity)];
	}
	return nullptr; // Specified Component does not exist 
}
template cSprite* ComponentStorage<cSprite>::RetrieveComponent(ENTITY entity);

/******************************************************************************/
/*!
  \brief	Whenever an entity is destroyed, check all the component List within
            componentArray and delete components that belong to that entity
*/
/******************************************************************************/
template<typename T>
void ComponentStorage<T>::EntityDestroyed(ENTITY entity)
{
	if (entityToIndexMap.find(entity) != componentArray.end())
	{
		// Remove the entity's component if it existed
		UnregisterComponent(entity);
	}
}
template void ComponentStorage<cSprite>::EntityDestroyed(ENTITY entity);