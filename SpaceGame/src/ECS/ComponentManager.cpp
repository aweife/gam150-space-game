#include "ComponentManager.h"					// Self Header
#include <typeinfo>								// typeid
#include "../Components/ComponentList.h"
#include "../Tools/Console.h"

void ComponentManager::Init()
{
	//Register all the components here
	RegisterComponentCollection<cTransform>(ID_TransformComponent);
	RegisterComponentCollection<cSprite>(ID_SpriteComponent);
	RegisterComponentCollection<cRigidBody>(ID_RigidBodyComponent);
	RegisterComponentCollection<cCollision>(ID_CollisionComponent);
	RegisterComponentCollection<cCamera>(ID_CameraComponent);
}

template<typename T>
void ComponentManager::RegisterComponentCollection(ComponentType id)
{
	const char* componentTypeName = typeid(T).name();
	//Component already registered and in storage 
	if (componentCollection.find(componentTypeName) != componentCollection.end()) return;	

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


void ComponentManager::GenerateComponentCollection() const
{
	Console_Cout("---Generating Component Collection List---");
	for (auto& element : componentCollection)
	{
		Console_Cout(element.first/*, (int) &element.second*/);
	}
	Console_Newline();
}

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

