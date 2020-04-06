/**********************************************************************************
* \file			aiIdleWander.cpp
* \brief		AI idle wander state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise idle wander of AI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void aiIdleWander::OnEnter(aiBlackBoard& bb)
{
	aiBase::OnEnter(bb);

	bb.rotationSpeed = bb.baseRotationSpeed / 2.0f;
	_distance = bb.baseAttackRange;
	FindRandomPosition();
}

void aiIdleWander::OnUpdate(aiBlackBoard& bb)
{
	if (AEVec2Distance(&_randomPosition, &trans->_position) > 10.0f)
	{
		Transform::RotateToTarget(trans->_rotation, trans->_position, _randomPosition, bb.rotationSpeed * g_dt);
		rb->_velocity += bb.baseAcceleration;
		if (rb->_velocity > bb.baseMaxSpeed / 2.0f)
			rb->_velocity = bb.baseMaxSpeed / 2.0f;

		Steering::SeekTarget(
			rb->_steeringVector,
			trans->_position, _randomPosition,
			rb->_velocity * g_dt * TurnToTarget(trans->_rotation, _randomPosition),
			rb->_velocityVector);

		if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange))
			ChangeState((AERandFloat() > 0.5f) ? STATE_CHASE : STATE_CHASEATTACK);
	}
	else
		ChangeState((AERandFloat() > 0.5f) ? STATE_IDLE : STATE_IDLEWANDER);
}

void aiIdleWander::OnExit(aiStateList& var)
{
	aiBase::OnExit(var);
}

void aiIdleWander::FindRandomPosition()
{
	AEVec2 desired = {AERandFloat(), AERandFloat()};
	AEVec2Normalize(&desired, &desired);
	AEVec2Scale(&desired, &desired, _distance);
	AEVec2Add(&_randomPosition, &trans->_position, &desired);
}

float aiIdleWander::TurnToTarget(const float& self, const AEVec2& target)
{
	AEVec2 selfRot{ cosf(self), sinf(self) };
	AEVec2 targetRot{ target };

	AEVec2Normalize(&selfRot, &selfRot);
	AEVec2Normalize(&targetRot, &targetRot);

	float dotAngle = AEVec2DotProduct(&selfRot, &targetRot);

	return (dotAngle < 0.0f ? 0.25f : dotAngle);
}