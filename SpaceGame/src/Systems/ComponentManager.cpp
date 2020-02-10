#include "ComponentManager.h"
#include <typeinfo>							 //  typeid
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Entity/EntityManager.h"

#include "../Tools/Console.h"
void ComponentManager::Init()
{
	//Register all the components here
	RegisterComponentCollection<SpriteComponent>(ID_SpriteComponent);
	RegisterComponentCollection<TransformComponent>(ID_TransformComponent);
}

template<typename T>
void ComponentManager::RegisterComponentCollection(COMPONENTID id)
{
	std::string componentTypeName = typeid(T).name();
	if (componentCollection.find(componentTypeName) != componentCollection.end()) return;	//Component already registered and have storage 

	//Create a new storage of components for that specific component type
	//To be shared by all relevant systems
	componentCollection.insert({ componentTypeName, std::make_shared<ComponentStorage<T>>()});

	//Create relevant mapping from typename to enum
	componentClassToEnum.insert({ componentTypeName, id });
}

void ComponentManager::AddOrRemoveEntitySignature(COMPONENTID id, int set, ENTITYID entity)
{
	SIGNATURE s = EntityManager::GetInstance().GetEntitySignature(entity);
	s.set(id, set);
	EntityManager::GetInstance().SetEntitySignature(entity, s);
}

template<typename T>
COMPONENTID ComponentManager::GetComponentID()
{
	std::string componentTypeName = typeid(T).name();

	AE_ASSERT(componentCollection.find(componentTypeName) != componentCollection.end()); //Component is not registered yet

	// Return component ID for creating signatures
	return componentClassToEnum[componentTypeName];
}

void ComponentManager::GenerateComponentCollection() const
{
	Console_Cout("---Generating Component Collection List---");
	for (auto& element : componentCollection)
	{
		Console_Cout(element.first/*, (int) &element.second*/);
	}
	Console_Newline();
}

template<typename T>
std::shared_ptr<ComponentStorage<T>> ComponentManager::GetComponentStorage()
{
	std::string componentTypeName = typeid(T).name();

	AE_ASSERT(componentCollection.find(componentTypeName) != componentCollection.end()); //Component is not registered yet

	return std::static_pointer_cast<ComponentStorage<T>>(componentCollection[componentTypeName]);
}


template<typename T>
void ComponentManager::AddComponent(ENTITYID entity, T* component)
{
	// Find the relevant component storage from collection, then insert the component into the storage
	//Component storage is shared pointer... component will be passed to unique pointer
	GetComponentStorage<T>()->RegisterComponent(entity, component);

	AddOrRemoveEntitySignature(GetComponentID<T>(), 1, entity);
}
//Explicit template
template void ComponentManager::AddComponent<SpriteComponent>(ENTITYID, SpriteComponent*);
template void ComponentManager::AddComponent<TransformComponent>(ENTITYID, TransformComponent*);

template<typename T>
void ComponentManager::RemoveComponent(ENTITYID entity)
{
	// Remove a component from the array for an entity
	GetComponentStorage<T>()->UnregisterComponent(entity);

	AddOrRemoveEntitySignature(GetComponentID<T>(), 0, entity);
}
//Explicit template
template void ComponentManager::RemoveComponent<SpriteComponent>(ENTITYID);


template<typename T>
T* ComponentManager::GetComponent(ENTITYID entity)
{
	return GetComponentStorage<T>()->RetrieveComponent(entity);
}
template SpriteComponent* ComponentManager::GetComponent(ENTITYID entity);

void ComponentManager::EntityDestroyed(ENTITYID entity)
{
	{
		// Check within each component storage if there was component for destroyed entity
		for (auto const& pair : componentCollection)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}
}

