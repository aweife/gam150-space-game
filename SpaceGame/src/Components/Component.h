#pragma once

#include <string>
#include "../Global_ECS.h"

enum sysCategory {
	SYS_NULL = 0,
	SYS_AI = 1, 
	SYS_GRAPHICS, 
	SYS_PHYSICS
};

//Components should only store data... but using class for now incase need functions
class Component
{
public:
	std::string			_name;			//Name of Component
	sysCategory			_category;		//Which system category - unused for now
	COMPONENTID			_componentID;	//Enum of Component 
	ENTITYID			_entityParent;	//Which enitity this component belongs to

	Component();
	virtual ~Component();	//virtual destructor to ensure our subclasses are correctly deallocated

	virtual void Init();
};

