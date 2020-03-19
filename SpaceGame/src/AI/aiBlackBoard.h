#pragma once

#include "../Global_ECS.h"
#include "AEVec2.h"

struct aiBlackBoard
{
	aiBlackBoard();

	ENTITY id;
	float distanceFromPlayer;
	AEVec2 directionToPlayer;
	AEVec2 directionToPlayerN;
	AEVec2 playerLastKnownPos;
	float positionUpdateTimer;

	// Self variables
	float attackRange;
	float maxSpeed;
	float acceleration;
	float rotationSpeed;
	float wanderAngle;
};
