/*********************************************************************************
* \file			ComponentStorage.h
* \brief		A tightly compact storage for a single component (templated)
* \author		Jun Yi, Chong, 50% Code Contribution
*        		Wei Feng, Ang, 50% Code Contribution
*
*				This component storage uses an array to densely pack components
*				together, allowing for linear access using index. To do this,
*				everytime a component is removed, the last component will be swapped
*				fill up the space. This storage also contains two direct mapping for
*				entity < -- > index of array, providing easy access using entity id
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include <unordered_map>				//storage type
#include <array>						//storage type
#include <memory>						//unique_ptr
#include "../Global_ECS.h"				//typedef alias for Entity
#include "ComponentStorage_Generic.h"	//Base class
#include "AEEngine.h"					//AE Assert

#include<typeinfo>
#include "../Tools/Console.h"
template<typename T>
class ComponentStorage :public ComponentStorage_Generic
{
private:
	//These 2 maps help to keep our component storage compact and help us find out their positions/entity relationship
	std::unordered_map<ENTITY, unsigned int> entityToIndexMap;			// Map from an entity ID to an array index.
	std::unordered_map<unsigned int, ENTITY> indexToEntityMap;			// Map from an array index to an entity ID.

	unsigned int currSize = 0;											// Current numbe of valid components in the array.
public:
	//Data
	std::array<std::unique_ptr<T>, MAX_ENTITIES> componentArray;		//A list of components based on entity

	/******************************************************************************/
	/*!
		\brief	Adds a component to its respective component storage,
				called by ComponentManager
	*/
	/******************************************************************************/
	void RegisterComponent(ENTITY entity, T* component)					//Adds a component to its component storage, tagged to its entity
	{
		if (entityToIndexMap.find(entity) != entityToIndexMap.end())
		{
			const char* buffer = typeid(T).name();
			Console_Cout(buffer);
		}
		AE_ASSERT(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component already exists");		//Component already exists

		

		//Update the index-entity relation map
		entityToIndexMap[entity] = currSize;
		indexToEntityMap[currSize] = entity;

		//Register the component into storage
		componentArray[currSize] = std::unique_ptr<T>{ component };

		// Increment count
		++currSize;
	}


	/******************************************************************************/
	/*!
		\brief	Remove a component to its respective component storage,
				called by ComponentManager
	*/
	/******************************************************************************/
	void UnregisterComponent(ENTITY entity)							//Remove a component from its respective component storage
	{
		AE_ASSERT(entityToIndexMap.find(entity) != entityToIndexMap.end());		//Component already does not exist

		unsigned int unregisterIndex = entityToIndexMap[entity];
		//Move the last element into the deleted component space...so that update will run without any gaps
		unsigned int backComponentIndex = currSize - 1;
		componentArray[unregisterIndex].swap(componentArray[backComponentIndex]); //Swap the content of unique pointers
		componentArray[backComponentIndex].reset();									// release and deallocate unique pointer

		//Update the index-entity relation map for the last element that has been moved
		ENTITY backEntity = indexToEntityMap[backComponentIndex];
		entityToIndexMap[backEntity] = unregisterIndex;
		indexToEntityMap[unregisterIndex] = backEntity;

		//Remove deleted component 
		entityToIndexMap.erase(entity);
		indexToEntityMap.erase(backComponentIndex);

		// Decrement count
		--currSize;
	}

	/******************************************************************************/
	/*!
		\brief	Returns a component to its that belong to an entity,
				Return nullptr if no such component found to that entity
				called by ComponentManager
	*/
	/******************************************************************************/
	T* RetrieveComponent(ENTITY entity)								//Return a pointer to the component that belongs to an entity
	{
		if (entityToIndexMap.find(entity) != entityToIndexMap.end()) //Check if the component exists in the array
		{
			return componentArray[entityToIndexMap[entity]].get(); //smart pointer dont offer automatic conversion
		}
		return nullptr; // Specified Component does not exist 
	}

	/******************************************************************************/
	/*!
		\brief	Whenever an entity is destroyed, check all the component List within
				componentArray and delete components that belong to that entity
	*/
	/******************************************************************************/
	void EntityDestroyed(ENTITY entity) override						//All Component Storage must react when a entity is destroyed
	{
		if (entityToIndexMap.find(entity) != entityToIndexMap.end())
		{
			// Remove the entity's component if it existed
			UnregisterComponent(entity);
		}
	}
};
