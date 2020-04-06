/**********************************************************************************
* \file			aiBlackBoard.h
* \brief		AI blackboard
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise blackboard of AI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "../Global_ECS.h"
#include "AEVec2.h"

enum AI_TYPE
{
	ENEMY = 0,
	BOSS,
	OBJECTIVE,
	DELIVERY,
	LEVEL_END,
};

struct aiBlackBoard
{
	aiBlackBoard(ENTITY entity, AI_TYPE type);
	void UpdateBlackboard();

	ENTITY id;
	AI_TYPE type;

	float distanceFromPlayer;
	AEVec2 directionToPlayer;
	AEVec2 directionToPlayerN;
	AEVec2 playerLastKnownPosition;
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
	bool markedForDestruction;
};

enum INNER_STATE
{
	INNER_STATE_ONENTER,
	INNER_STATE_ONUPDATE,
	INNER_STATE_ONEXIT,
};
