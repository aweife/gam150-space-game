/**********************************************************************************
* \file			aiBlackBoard.cpp
* \brief		AI blackboard
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise blackboard of AI
*				- Contains common data used by many AI agents
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "aiBlackBoard.h"
#include "../Player/PlayerManager.h"
#include "../ECS/Core.h"						//Work with ECS
#include "../Global.h"
#include "../Levels/Level3.h"					// For level 3 escort mission
#include "../Managers/GameStateManager.h"

aiBlackBoard::aiBlackBoard(ENTITY entity, AI_TYPE type):
	id {entity},
	type {type},

	positionUpdateTimer{0.0f},

	baseAttackRange{ 250.0f },
	baseDetectRange{350.0f},
	baseMaxSpeed{ 80.0f },
	baseAcceleration{ 5.0f },
	baseRotationSpeed{ 5.0f },

	wanderAngle{ 0.0f },
	markedForDestruction{false}
{}

void aiBlackBoard::UpdateBlackboard()
{
	ENTITY pid;
	if(currentState == GS_LEVEL3) 
	{
		// If level 3, main target is escort
		pid = GetEscort();

		// When escort dies
		if (pid == 0)
		{
			// If mission pass, main target becomes player
			if(EscortMissionSuccess())
				pid = PlayerManager::player;
			else // Else game ends
				pid = 0;
		}
	}
	else
	{
		pid = PlayerManager::player;
	}

	//NO ACTIVE PLAYER
	if (pid == 0)	return;				

	// Get components
	cTransform* self = Core::Get().GetComponent<cTransform>(id);
	cTransform* player = Core::Get().GetComponent<cTransform>(pid);

	// Calculate distance
	distanceFromPlayer = AEVec2Distance(&player->_position, &self->_position);

	// Calculate vector towards player
	AEVec2 temp;
	AEVec2Sub(&temp, &player->_position, &self->_position);
	directionToPlayer = temp;
	AEVec2Normalize(&temp, &temp);
	directionToPlayerN = temp;

	// Update player last known position
	positionUpdateTimer += g_dt;
	if (positionUpdateTimer > 0.5f)
	{
		positionUpdateTimer = 0.0f;

		// Store
		playerLastKnownPosition = player->_position;
	}
}
