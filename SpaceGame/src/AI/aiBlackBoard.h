#pragma once

#include "../Global_ECS.h"
#include "AEVec2.h"

struct aiBlackBoard
{
	aiBlackBoard();
	void UpdateBlackboard(ENTITY id);

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

enum INNER_STATE
{
	INNER_STATE_ONENTER,
	INNER_STATE_ONUPDATE,
	INNER_STATE_ONEXIT,
};
