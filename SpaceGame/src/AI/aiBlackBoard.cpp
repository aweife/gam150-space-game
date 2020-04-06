#include "aiBlackBoard.h"
#include "../Player/PlayerManager.h"
#include "../ECS/Core.h"						//Work with ECS
#include "../Global.h"

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
	//NO ACTIVE PLAYER
	const ENTITY pid = PlayerManager::player;
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
