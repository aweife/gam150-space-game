/**********************************************************************************
* \file			aiAttack.cpp
* \brief		AI attack state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise attack state of AI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "../aiState.h"

#include "../../ECS/Core.h"
#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"

void aiAttack::OnEnter(aiBlackBoard& bb)
{
	// Set distances for state transiton
	_minDistance = bb.baseAttackRange / 2.0f;
	_maxDistance = bb.baseAttackRange * 2.0f;
	_minStay = 3.0f + (AERandFloat() * 2.0f);

	// Cache self components
	rwp = Core::Get().GetComponent<cRangeWeapon>(bb.id);

	aiBase::OnEnter(bb);
}

void aiAttack::OnUpdate(aiBlackBoard& bb)
{
	// Slowdown
	if (rb->_velocity > rb->_acceleration)
		rb->_velocity *= 0.9f;

	// Always aim at player in this state
	Transform::RotateToTarget(trans->_rotation, bb.directionToPlayerN, bb.baseRotationSpeed * g_dt);

	// Attack with timer
	if (Check::LessThanRange(bb.distanceFromPlayer, _maxDistance))
	{
		Attack();

		_minStay -= g_dt;

		// If too close to player
		if (Check::LessThanRange(bb.distanceFromPlayer, _minDistance) || _minStay < 0.0f)
			ChangeState((AERandFloat() > 0.5f) ? STATE_RETREAT : STATE_RETREATATTACK);
	}
	else
		ChangeState((AERandFloat() > 0.5f) ? STATE_CHASE : STATE_CHASEATTACK);
}

void aiAttack::OnExit(aiStateList& var)
{
	rwp->_enemyIsShooting = false;

	aiBase::OnExit(var);
}

void aiAttack::Attack()
{
	rwp->_enemyIsShooting = true;
}
