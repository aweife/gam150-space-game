#pragma once

#include "../Global_ECS.h"		//typedef alias for Entity
#include "Component.h"			//Access to component base class
#include <unordered_map>
#include <memory>

#include "ComponentStorage_Generic.h"

template<typename T>
class ComponentStorage:public ComponentStorage_Generic
{
private:
	//These 2 maps help to keep our component storage compact and help us find out their positions/entity relationship
	std::unordered_map<ENTITY, unsigned int> entityToIndexMap;			// Map from an entity ID to an array index.
	std::unordered_map<unsigned int, ENTITY> indexToEntityMap;			// Map from an array index to an entity ID.
		
	unsigned int currSize;												// Current numbe of valid components in the array.
public:
	//Data
	std::array<std::unique_ptr<T>, MAX_ENTITIES> componentArray;			//A list of components based on entity

	//Functions
	void RegisterComponent(ENTITY entity, T* component);				//Adds a component to its component storage, tagged to its entity

	void UnregisterComponent(ENTITY entity);							//Remove a component from its respective component storage

	T* RetrieveComponent(ENTITY entity);								//Return a pointer to the component that belongs to an entity

	void EntityDestroyed(ENTITY entity) override;						//All Component Storage must react when a entity is destroyed
};
//NOT SURE IF CAN TEMPLATE SPECIFICATION HERE??