#pragma once

#include <unordered_map>						//unordered map
#include <memory>								//unique pointer
#include "ComponentStorage.h"					//Storage used to contain all components of same kind

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
	~ComponentManager()
	{
		printf("Component Manager Destructor");
	}
	virtual void Init();																//Register all components to use into a library

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* componentTypeName = typeid(T).name();

		AE_ASSERT(componentCollection.find(componentTypeName) != componentCollection.end()); //Component is not registered yet

		// Return component ID for creating signatures
		return componentClassToEnum[componentTypeName];
	}

	void GenerateComponentCollection() const;											//Debug feature

	template<typename T>
	std::shared_ptr<ComponentStorage<T>> GetComponentStorage()
	{
		const char* componentTypeName = typeid(T).name();

		AE_ASSERT(componentCollection.find(componentTypeName) != componentCollection.end()); //Component is not registered yet

		return std::static_pointer_cast<ComponentStorage<T>>(componentCollection[componentTypeName]);
	}

	template<typename T>
	void AddComponent(ENTITY entity, T* component)
	{
		// Find the relevant component storage from collection, then insert the component into the storage
		//Component storage is shared pointer... component will be passed to unique pointer
		GetComponentStorage<T>()->RegisterComponent(entity, component);
	}

	template<typename T>
	void RemoveComponent(ENTITY entity)
	{
		// Remove a component from the array for an entity
		GetComponentStorage<T>()->UnregisterComponent(entity);
	}

	void RemoveAllComponent()
	{
		for (auto i : componentCollection) 
		{
			i.second.reset();
		}
	}

	template<typename T>
	T* GetComponent(ENTITY entity)
	{
		return GetComponentStorage<T>()->RetrieveComponent(entity);
	}

	void EntityDestroyed(ENTITY entity);
};

