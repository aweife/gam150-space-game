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

		// If too close to player
		if (Check::LessThanRange(bb.distanceFromPlayer, _minDistance))
			ChangeState(STATE_RETREAT);
	}
	else
		ChangeState(STATE_CHASE);
}

void aiAttack::OnExit(aiStateList& var)
{
	rwp->_isShooting = false;

	aiBase::OnExit(var);
}

void aiAttack::Attack()
{
	rwp->_isShooting = true;
}
