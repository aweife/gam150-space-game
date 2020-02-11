#pragma once

#include "System.h"
#include "../Components/ComponentStorage.h"
#include <unordered_map>						//unordered map
#include <memory>								//unique pointer
#include <string>								//to match typeid

class ComponentManager : public System<ComponentManager>
{
private:

	std::unordered_map																	//A library of all components in game
		<std::string, std::shared_ptr<ComponentStorage_Generic>> componentCollection;

	std::unordered_map																	//Map a Component class type to Component Enum...
		<std::string, COMPONENTID> componentClassToEnum;								//Useful for changing signature bitset

	template<typename T>
	void RegisterComponentCollection(COMPONENTID id);									//Register each components into a library

	void AddOrRemoveEntitySignature(COMPONENTID id, int set, ENTITYID entity);

public:
	virtual void Init();																//Register all components to use into a library

	template<typename T>
	COMPONENTID GetComponentID();

	void GenerateComponentCollection() const;											//Debug feature

	template<typename T>
	std::shared_ptr<ComponentStorage<T>> GetComponentStorage();

	template<typename T>
	void AddComponent(ENTITYID entity, T* component);

	template<typename T>
	void RemoveComponent(ENTITYID entity);

	template<typename T>
	T* GetComponent(ENTITYID entity);

	void EntityDestroyed(ENTITYID entity);
};

