#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include <typeinfo>						// operator typeid
#include "../Components/Component.h"
#include "../Systems/MemoryPool.h"

class GameObject
{
public:
	std::string		_name;						//Name of GameObject
	unsigned short	_heirachy;					//Order inside GameObject Manager
	std::vector<Component> componentList;		// Vector of components
	int component_bitflag;						// Bitflag for active component


	//Constructor
	GameObject(const std::string& name, unsigned short heirachy);
	~GameObject();

	//Need to specify source code in header due to compiler accessibility
	//https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
	//Example:GameObject.AddComponent<MeshComponent>();
	template<class AnyClass> void AddComponent()
	{
		MemoryPool& memPool = MemoryPool::GetInstance();
		Component* addComponent = new(memPool.Allocate(sizeof(AnyClass))) AnyClass();

		componentList.push_back(*addComponent);
	}

	template<class AnyClass> void RemoveComponent()
	{
		MemoryPool& memPool = MemoryPool::GetInstance();

		for (auto i = componentList.begin(); i != componentList.end(); ++i)
		{
			if (i->_name.compare(typeid(AnyClass).name()) == 0)
			{
				Component foundComponent = *i;
				componentList.erase(i);
				//memPool.Deallocate(sizeof(AnyClass), &foundComponent);
				break;
			}
		}
	}
};

#endif // !GAMEOBJECT_H
