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

	// Const
	const float baseAttackRange;
	const float baseDetectRange;
	const float baseMaxSpeed;
	const float baseAcceleration;
	const float baseRotationSpeed;

	// These are used by states
	float wanderAngle;
	float rotationSpeed;
};
