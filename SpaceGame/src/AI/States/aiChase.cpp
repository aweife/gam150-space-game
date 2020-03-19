#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void aiChase::OnEnter(aiBlackBoard& bb)
{
	aiBase::OnEnter(bb);

	// Initialize state
	rb->_velocityCap = bb.baseMaxSpeed;
	_chaseTimer = 0.0f;
}

void aiChase::OnUpdate(aiBlackBoard& bb)
{
	rb->_velocity += bb.baseAcceleration;
	Steering::SeekTarget(rb->_steeringVector, bb.directionToPlayerN, rb->_velocity * g_dt, rb->_velocityVector);
	Steering::Wander(rb->_steeringVector, rb->_velocityDirection, bb.wanderAngle, 1.0f);
	Transform::RotateToTarget(trans->_rotation, bb.directionToPlayerN, bb.baseRotationSpeed * g_dt);

	// If close enought to attack
	if (bb.distanceFromPlayer < bb.baseAttackRange)
	{
		// Change inner state
		innerState = INNER_STATE_ONEXIT;
		nextState = STATE_ATTACK;
	}

	// Transit to pursuit
	_chaseTimer += g_dt;
	if (_chaseTimer > 5.0f)
		ChangeState(STATE_PURSUIT);
}

void aiChase::OnExit(aiStateList& var)
{
	aiBase::OnExit(var);
}
