#include "Component.h"

#include "../Tools/Console.h"				//REMOVE AFTER TESTING

Component::Component() :_category{SYS_NULL}, _componentID{ID_NullComponent}, _entityParent{ 0 }
{
	Console_Cout("Component Constructor");	//REMOVE AFTER TESTING
}

Component::~Component()
{
	Console_Cout("Component Destructor");	//REMOVE AFTER TESTING
}

void Component::Init()
{
	Console_Cout("Component INIT");	//REMOVE AFTER TESTING
}