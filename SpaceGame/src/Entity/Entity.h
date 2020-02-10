#pragma once

#include "../Global_ECS.h"

class Entity
{
private:
	SIGNATURE _signature;
	ENTITYID _entityID;
public:
	Entity(std::string);
};