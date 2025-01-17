#pragma once

#include <set>							//entitiesList
#include "../Global_ECS.h"

class System
{
public:
	// Using a set instead of a list because every element in a set is unique
	// Also for the convienent insert() and erase() functionality
	std::set<ENTITY> entitiesList;

	// Every system that inherits from this base class must implement these 
	// functions
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void OnComponentAdd(ENTITY entity) = 0;
	virtual void OnComponentRemove(ENTITY entity) = 0;

	System() = default;
	virtual ~System() = default;
};
