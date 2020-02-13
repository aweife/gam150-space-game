#pragma once

#include "../Global_ECS.h"				//typedef alias for Entity
#include "../Components/Component.h"	//Access to component base class
#include <unordered_map>				//storage type
#include <array>						//storage type
#include <memory>						//unique_ptr
#include "ComponentStorage_Generic.h"	//Base class
#include "../Components/Component.h"	//Header to all types of component used in game
#include "AEEngine.h"

template<typename T>
class ComponentStorage :public ComponentStorage_Generic
{
private:
	//These 2 maps help to keep our component storage compact and help us find out their positions/entity relationship
	std::unordered_map<ENTITY, unsigned int> entityToIndexMap;			// Map from an entity ID to an array index.
	std::unordered_map<unsigned int, ENTITY> indexToEntityMap;			// Map from an array index to an entity ID.

	unsigned int currSize;												// Current numbe of valid components in the array.
public:
	//Data
	std::array<std::unique_ptr<T>, MAX_ENTITIES> componentArray;		//A list of components based on entity

	//Functions
	void RegisterComponent(ENTITY entity, T* component)					//Adds a component to its component storage, tagged to its entity
	{
		AE_ASSERT(entityToIndexMap.find(entity) == entityToIndexMap.end());		//Component already exists

		//Update the index-entity relation map
		entityToIndexMap[entity] = currSize;
		indexToEntityMap[currSize] = entity;

		//Register the component into storage
		componentArray[currSize] = std::unique_ptr<T>{ component };

		// Increment count
		++currSize;
	}

	void UnregisterComponent(ENTITY entity)							//Remove a component from its respective component storage
	{
		AE_ASSERT(entityToIndexMap.find(entity) != entityToIndexMap.end());		//Component already does not exist

		unsigned int unregisterIndex = entityToIndexMap[entity];
		//Move the last element into the deleted component space...so that update will run without any gaps
		unsigned int backComponentIndex = currSize - 1;
		componentArray[unregisterIndex].swap(componentArray[backComponentIndex]); //Swap the content of unique pointers
		componentArray[backComponentIndex].reset();									// release and deallocate unique pointer

		//Update the index-entity relation map for the last element that has been moved
		ENTITY backEntity = entityToIndexMap[backComponentIndex];
		entityToIndexMap[backEntity] = unregisterIndex;
		indexToEntityMap[unregisterIndex] = backEntity;

		//Remove deleted component 
		entityToIndexMap.erase(entity);
		indexToEntityMap.erase(backComponentIndex);

		// Decrement count
		--currSize;
	}
	T* RetrieveComponent(ENTITY entity)								//Return a pointer to the component that belongs to an entity
	{
		if (entityToIndexMap.find(entity) != entityToIndexMap.end()) //Check if the component exists in the array
		{
			return componentArray[entityToIndexMap[entity]].get(); //smart pointer dont offer automatic conversion
		}
		return nullptr; // Specified Component does not exist 
	}
	void EntityDestroyed(ENTITY entity) override						//All Component Storage must react when a entity is destroyed
	{
		if (entityToIndexMap.find(entity) != entityToIndexMap.end())
		{
			// Remove the entity's component if it existed
			UnregisterComponent(entity);
		}
	}
};
