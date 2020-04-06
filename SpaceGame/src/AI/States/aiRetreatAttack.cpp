/**********************************************************************************
* \file			aiRetreatAttack.cpp
* \brief		AI retreat attack state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise retreat attack state of AI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Editor.h"

void aiRetreatAttack::OnEnter(aiBlackBoard& bb)
{
	aiBase::OnEnter(bb);

	// Cache self components
	rwp = Core::Get().GetComponent<cRangeWeapon>(bb.id);

	// Initialise state
	bb.rotationSpeed = bb.baseRotationSpeed / 2.0f;
	_safeDistance = 700.0f + bb.baseAttackRange;
	FindSafePosition(bb);
}

void aiRetreatAttack::OnUpdate(aiBlackBoard& bb)
{
	if (AEVec2Distance(&_safePosition, &trans->_position) > 10.0f)
	{
		Transform::RotateToTarget(trans->_rotation, trans->_position, bb.playerLastKnownPosition, bb.rotationSpeed * g_dt);
		rb->_velocity += bb.baseAcceleration;

		Steering::SeekTarget(
			rb->_steeringVector,
			trans->_position, _safePosition,
			rb->_velocity * g_dt * TurnToTarget(trans->_rotation, _safePosition),
			rb->_velocityVector);

		Attack();
	}
	else
		ChangeState((AERandFloat() > 0.5f) ? STATE_CHASE : STATE_CHASEATTACK);
}

void aiRetreatAttack::OnExit(aiStateList& var)
{
	aiBase::OnExit(var);
}

void aiRetreatAttack::FindSafePosition(const aiBlackBoard& bb)
{
	AEVec2 desired = bb.directionToPlayerN;
	AEVec2Neg(&desired, &desired);
	AEVec2Scale(&desired, &desired, _safeDistance);
	AEVec2Add(&_safePosition, &trans->_position, &desired);
}

float aiRetreatAttack::TurnToTarget(const float& self, const AEVec2& target)
{
	AEVec2 selfRot{ cosf(self), sinf(self) };
	AEVec2 targetRot{ target };

	AEVec2Normalize(&selfRot, &selfRot);
	AEVec2Normalize(&targetRot, &targetRot);

	float dotAngle = AEVec2DotProduct(&selfRot, &targetRot);
	return (dotAngle < 0.0f ? 0.25f : dotAngle);
}

void aiRetreatAttack::Attack()
{
	rwp->_enemyIsShooting = true;
}
