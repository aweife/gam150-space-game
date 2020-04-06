/**********************************************************************************
* \file			Component.h
* \brief		Base class for all components to inherit from
* \author		Jun Yi,   Chong,  50% Code Contribution
*				Wei Feng,   Ang,  50% Code Contribution
*
*				Responsible for the components of the engine
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
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

