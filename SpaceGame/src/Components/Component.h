#pragma once

#include "../Global_ECS.h"	//typedef allias

//Components should only store data... but using class for now incase need functions
class Component
{
public:
	const char*			_name				= "";						// Name of Component
	ComponentType		_componentID		= ID_NullComponent;			// Enum of Component 
	ENTITY				_entityParent		= 0;						// Which enitity this component belongs to

	Component() = default;												
	virtual ~Component() = default;						// Virtual destructor to ensure our subclasses are correctly deallocated
};

