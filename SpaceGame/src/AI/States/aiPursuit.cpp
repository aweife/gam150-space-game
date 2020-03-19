#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"
#include "../../Player/PlayerManager.h"


void aiPursuit::OnEnter(aiBlackBoard& bb)
{
	// Cache player
	ptrans = Core::Get().GetComponent<cTransform>(PlayerManager::player);
	prb = Core::Get().GetComponent<cRigidBody>(PlayerManager::player);

	_pursuitTimer = 0.0f;

	aiBase::OnEnter(bb);
}

void aiPursuit::OnUpdate(aiBlackBoard& bb)
{
	_pursuitTimer += g_dt;
	_positionPrediction = _pursuitTimer / 2.0f;
	if (_positionPrediction > prb->_velocity)
	{
		_pursuitTimer = 1.0f;
		_positionPrediction = prb->_velocity;
	}

	rb->_velocity += bb.baseAcceleration;
	Steering::Pursuit(rb->_steeringVector, _futureTargetPosition, _positionPrediction, ptrans->_position, prb->_velocityVector, trans->_position, rb->_velocity * g_dt, rb->_velocityVector);
	Steering::Wander(rb->_steeringVector, rb->_velocityDirection, bb.wanderAngle, 0.5f);

	// Look at target pos
	Transform::RotateToTarget(trans->_rotation, bb.playerLastKnownPosition, bb.baseRotationSpeed * g_dt);

	// Check close enough to attack or not
	AEVec2Sub(&_targetPosition, &_futureTargetPosition, &trans->_position);
	_distanceFromTarget = AEVec2Length(&_targetPosition);

	// If close enough to attack
	if (_distanceFromTarget < bb.baseAttackRange)
		ChangeState(STATE_ATTACK);
}

void aiPursuit::OnExit(aiStateList& var)
{
	aiBase::OnExit(var);
}
