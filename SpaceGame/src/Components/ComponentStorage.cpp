#include "ComponentStorage.h"
#include "AEEngine.h"
#include "SpriteComponent.h"
#include "../Components/TransformComponent.h"

template<typename T>
void ComponentStorage<T>::RegisterComponent(ENTITYID entity, T* component)
{
	AE_ASSERT(componentMap.find(entity) == componentMap.end());		//Component already exists

	componentMap.insert({ entity, std::unique_ptr<T>{component} });
}
template void ComponentStorage<SpriteComponent>::RegisterComponent(ENTITYID entity, SpriteComponent* component);
template void ComponentStorage<TransformComponent>::RegisterComponent(ENTITYID entity, TransformComponent* component);

template<typename T>
void ComponentStorage<T>::UnregisterComponent(ENTITYID entity)
{
	AE_ASSERT(componentMap.find(entity) != componentMap.end());		//Component already does not exist

	componentMap.erase(entity);
}
template void ComponentStorage<SpriteComponent>::UnregisterComponent(ENTITYID entity);
template void ComponentStorage<TransformComponent>::UnregisterComponent(ENTITYID entity);

template<typename T>
T* ComponentStorage<T>::RetrieveComponent(ENTITYID entity)
{
	AE_WARNING_MESG(componentMap.find(entity) != componentMap.end(), "Specified Component does not exist ");
	if (componentMap.find(entity) != componentMap.end()) // Specified Component does not exist 
	{
		return componentMap[entity].get();
	}
	
	return nullptr;
}
template SpriteComponent* ComponentStorage<SpriteComponent>::RetrieveComponent(ENTITYID entity);
template TransformComponent* ComponentStorage<TransformComponent>::RetrieveComponent(ENTITYID entity);


template<typename T>
void ComponentStorage<T>::EntityDestroyed(ENTITYID entity)
{
	if (componentMap.find(entity) != componentMap.end())
	{
		// Remove the entity's component if it existed
		UnregisterComponent(entity);
	}
}
template void ComponentStorage<SpriteComponent>::EntityDestroyed(ENTITYID entity);
template void ComponentStorage<TransformComponent>::EntityDestroyed(ENTITYID entity);