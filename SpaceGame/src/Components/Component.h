#pragma once

#include "../Global_ECS.h"	//typedef allias

//Components should only store data... but using class for now incase need functions
class Component
{
public:
	const char*			_name				= "";						// Name of Component
	SYSCATEGORY			_category			= SYS_NULL;					// Which system category - unused for now
	ComponentType		_componentID		= ID_NullComponent;			// Enum of Component 
	ENTITY				_entityParent		= 0;						// Which enitity this component belongs to

	Component() = default;												
	virtual ~Component() = default;										//virtual destructor to ensure our subclasses are correctly deallocated

	virtual void Init() = 0;											//Pure Virtual
};

