#pragma once

#include "../Global.h"
#include "Component.h"

enum PATH_STATE
{
	PATH_SEEK = 0,
	PATH_FLEE,
};

class cPathFinding:public Component
{
public:
	ENTITY target;
	PATH_STATE currentState;
};