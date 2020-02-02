#pragma once

#include "../Global_ECS.h"
#include "Component.h"
#include <unordered_map>
#include <memory>

#include "AEEngine.h"			//REMOVE AFTER TESTING
#include "ComponentStorage_Generic.h"

template<typename T>
class ComponentStorage:public ComponentStorage_Generic
{
private:
	
public:
	std::unordered_map<ENTITYID, std::unique_ptr<T>> componentMap;		//A list of components based on entity

	void RegisterComponent(ENTITYID entity, T* component);

	void UnregisterComponent(ENTITYID entity);

	T* RetrieveComponent(ENTITYID entity);

	void EntityDestroyed(ENTITYID entity) override;
};