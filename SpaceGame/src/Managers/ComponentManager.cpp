#include "ComponentManager.h"					// Self Header
#include <typeinfo>								// typeid
#include "../Components/ComponentList.h"
#include "EntityManager.h"
#include "../Global_ECS.h"

#include "../Tools/Console.h"
void ComponentManager::Init()
{
	//Register all the components here
	RegisterComponentCollection<cSprite>(ID_SpriteComponent);
}

template<typename T>
void ComponentManager::RegisterComponentCollection(ComponentType id)
{
	const char* componentTypeName = typeid(T).name();
	if (componentCollection.find(componentTypeName) != componentCollection.end()) return;	//Component already registered and have storage 

	//Create a new storage of components for that specific component type
	//To be shared by all relevant systems
	componentCollection.insert({componentTypeName, std::make_shared<ComponentStorage<T>>()});

	//Create relevant mapping from typename to enum
	componentClassToEnum.insert({componentTypeName, id });
}

//void ComponentManager::AddOrRemoveEntitySignature(ComponentType id, int set, ENTITY entity)
//{
//	SIGNATURE s = EntityManager.GetEntitySignature(entity);
//	s.set(id, set);
//	EntityManager.SetEntitySignature(entity, s);
//}

template<typename T>
COMPONENTID ComponentManager::GetComponentType()
{
	const char* componentTypeName = typeid(T).name();

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
//Explicit template
template void ComponentManager::AddComponent<cSprite>(ENTITY, cSprite*);

template<typename T>
void ComponentManager::AddComponent(ENTITY entity, T* component)
{
	// Find the relevant component storage from collection, then insert the component into the storage
	//Component storage is shared pointer... component will be passed to unique pointer
	GetComponentStorage<T>()->RegisterComponent(entity, component);

}
//Explicit template
template void ComponentManager::AddComponent<cSprite>(ENTITY, cSprite*);

template<typename T>
void ComponentManager::RemoveComponent(ENTITY entity)
{
	// Remove a component from the array for an entity
	GetComponentStorage<T>()->UnregisterComponent(entity);

}
//Explicit template
template void ComponentManager::RemoveComponent<cSprite>(ENTITY);

template<typename T>
T* ComponentManager::GetComponent(ENTITY entity)
{
	return GetComponentStorage<T>()->RetrieveComponent(entity);
}
template cSprite* ComponentManager::GetComponent(ENTITY entity);

void ComponentManager::EntityDestroyed(ENTITY entity)
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

