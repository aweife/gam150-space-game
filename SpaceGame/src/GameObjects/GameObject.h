#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "../Components/Component.h"
class GameObject
{
public:
	std::string		_name;		//Name of GameObject
	unsigned short	_heirachy;	//Order inside GameObject Manager

	std::vector<Component> componentList;		// Vector of components
	int component_bitflag;						// Bitflag for active component
	GameObject(const std::string& name, unsigned short heirachy);
};

#endif // !GAMEOBJECT_H
