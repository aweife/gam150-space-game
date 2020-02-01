#pragma once

#include <string>
#include <vector>
#include "../Components/Component.h"			// Component Class Type
	
#include<iostream>
class GameObject
{
public:
	std::string		_name;						// Name of GameObject
	unsigned short	_id;					// Order inside GameObject Manager
	std::vector<std::unique_ptr<Component>> componentList;		// Vector of components - raw pointer
	int component_bitflag;						// Bitflag for active component


	//Constructor and Destructor
	GameObject(const std::string& name, unsigned short heirachy);
	~GameObject();

	// Component related funcitons
	template<class AnyComp> void AddComponent();
	template<class AnyComp> void RemoveComponent();
};
