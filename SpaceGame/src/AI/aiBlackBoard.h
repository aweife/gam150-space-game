#pragma once

#include "../Global_ECS.h"
#include "AEEngine.h"

struct aiBlackBoard
{
	ENTITY id;
	float distanceFromPlayer;
	AEVec2 directionToPlayer;
};
