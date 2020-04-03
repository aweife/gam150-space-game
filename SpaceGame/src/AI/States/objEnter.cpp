#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"

#include "../../ECS/Factory.h"
#include "../../Managers/LevelManager.h"

void objEnter::OnEnter(aiBlackBoard& bb)
{
	aiBase::OnEnter(bb);

	// Initialize state
	_stayDuration = 5.0f;
	_stayTimer = 0.0f;
}

void objEnter::OnUpdate(aiBlackBoard& bb)
{
	// If we leave the objective
	if (!Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange/2.0f))
		ChangeState(STATE_IDLE);

	// Keep track of how long we are staying near the objective
	_stayTimer += g_dt;

	// Basic feedback for now
	// TODO: make particles fly towards player
	trans->_rotation += _stayTimer * PI;

	// When we stayed long enough
	if (_stayTimer > _stayDuration)
	{
		switch (bb.type)
		{
		case OBJECTIVE:

			// Clear the objective
			Factory::CreateParticleEmitter_UPONIMPACT(trans);
			LevelManager::ClearObjective(bb.id);
			ChangeState(STATE_IDLE);
			bb.markedForDestruction = true;

			break;
		case LEVEL_END:

			// Escape and transit to next level


			break;
		}
	}
}

void objEnter::OnExit(aiStateList& var)
{
	// Reset
	trans->_rotation = 0.0f;

	aiBase::OnExit(var);
}