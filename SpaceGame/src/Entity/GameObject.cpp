#include "GameObject.h"
#include <string>
#include <typeinfo>							// operator typeid
#include <algorithm>						 // std::remove

//Add or remove components template
#include "../Components/MeshComponent.h"

#include "../Tools/Console.h"				//REMOVE AFTER TESTING

GameObject::GameObject(const std::string& name, unsigned short id)
	:_name{ name }, _id{ id }, component_bitflag{ 0 }
{
}

GameObject::~GameObject()
{
	//Delete components inside vector done by unique pointer
	componentList.clear();
	Console_Cout("GameObject Destructor");	//REMOVE AFTER TESTING
}

template<class AnyComp>
void GameObject::AddComponent()
{
	Component* newComponent = new AnyComp();	
	componentList.push_back(std::unique_ptr<Component>{newComponent});
}
//explict template instances
template void GameObject::AddComponent<MeshComponent>();

template<class AnyComp>
void GameObject::RemoveComponent()
{
	for (auto i = componentList.begin(); i != componentList.end(); ++i)
	{
		if ((*i)->_name.compare(typeid(AnyComp).name()) == 0)
		{
			componentList.erase(i);
			break;
		}
	}
}
//explict template instances
template void GameObject::RemoveComponent<MeshComponent>();