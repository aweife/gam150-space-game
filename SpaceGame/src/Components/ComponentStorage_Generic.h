#pragma once

class ComponentStorage_Generic							//Abstract class
{
public:
	virtual ~ComponentStorage_Generic() = default;		//Derived destructor for Component Storage
	virtual void EntityDestroyed(ENTITY entity) = 0;	//Pure virtual function	
};