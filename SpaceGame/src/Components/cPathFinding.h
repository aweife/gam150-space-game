#pragma once

#include "../Global.h"
#include "Component.h"

enum PATH_STATE
{
	PATH_SEEK = 0,
	PATH_FLEE,
	PATH_UNKNOWN
};

class cPathFinding:public Component
{
public:
	ENTITY target					 = 0;//Zero is not supposed to be used by any entity
	PATH_STATE currentState			 = PATH_UNKNOWN;
};