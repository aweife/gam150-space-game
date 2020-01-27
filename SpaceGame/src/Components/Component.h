#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

enum sysCategory {
	SYS_AI = 0, 
	SYS_GRAPHICS, 
	SYS_PHYSICS
};

class Component
{
public:
	std::string			_name;		//Name of Component
	sysCategory		_category;		//Name of GameObject
	short			_bitfieldIndex;

	void InitComponent();
};

#endif // !COMPONENT_H

//Component index List
// GRAPHICS
// 1 = meshcomponent