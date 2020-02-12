#pragma once

#include <set>
#include "../Global_ECS.h"

class System
{
public:
	// Using a set instead of a list because every element in a set is unique
	// Also for the convienent insert() and erase() functionality
	std::set<ENTITY> entitiesList;
};



//#include "../Global_ECS.h"
//#include "AEEngine.h"
//
//template<typename T>
//class System
//{
//private:
//	// Null value set before execution of program, Instance will be created on demand.
//	static T* instance;			/* Here will be the instance stored. */
//	
//
//	System(const System&) = delete;
//	System& operator=(const System) = delete;
//protected:
//	System() 
//	{
//		_systemSignature = 0;
//	};
//	virtual ~System() { };
//
//public:
//	SIGNATURE _systemSignature;  // Indicate what components the system wil manage
//
//	//Manager instance functions
//	static T& GetInstance();				/* Static access method. */
//	static void DestroyInstance();
//	virtual void Init() {};
//	virtual void Update() {};
//};
//
//template<typename T> T* System<T>::instance = nullptr;
//
//template<typename T>
//T& System<T>::GetInstance()			/* Static access method. */
//{
//	if (instance == nullptr)
//	{
//		instance = new T();
//	}
//
//	AE_ASSERT(instance);	//Assert if fail
//	return *instance;
//}
//
//template<typename T>
//void System<T>::DestroyInstance()
//{
//	// Delete singleton instance
//	delete(instance);
//}
