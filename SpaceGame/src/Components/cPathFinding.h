#pragma once

#include "../Global.h"

enum PATH_STATE
{
	PATH_SEEK = 0,
	PATH_FLEE,
};

class cPathFinding
{
public:
	ENTITY target;
	PATH_STATE currentState;
};