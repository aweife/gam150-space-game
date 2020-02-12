#pragma once

#include "../Components/ComponentStorage.h"		//Storage used to contain all components of same kind
#include <unordered_map>						//unordered map
#include <memory>								//unique pointer

class ComponentManager
{
private:

	std::unordered_map																	//A library of all components in game
		<const char*, std::shared_ptr<ComponentStorage_Generic>> componentCollection;

	std::unordered_map																	//Map a Component class type to Component Enum...
		<const char*, ComponentType> componentClassToEnum;								//Useful for changing signature bitset

	template<typename T>
	void RegisterComponentCollection(ComponentType id);									//Register each components into a library

	//void AddOrRemoveEntitySignature(ComponentType id, int set, ENTITY entity);

public:
	virtual void Init();																//Register all components to use into a library

	template<typename T>
	COMPONENTID GetComponentType();

	void GenerateComponentCollection() const;											//Debug feature

	template<typename T>
	std::shared_ptr<ComponentStorage<T>> GetComponentStorage();

	template<typename T>
	void AddComponent(ENTITY entity, T* component);

	template<typename T>
	void RemoveComponent(ENTITY entity);

	template<typename T>
	T* GetComponent(ENTITY entity);

	void EntityDestroyed(ENTITY entity);
};

