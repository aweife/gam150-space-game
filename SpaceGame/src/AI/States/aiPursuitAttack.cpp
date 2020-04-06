/**********************************************************************************
* \file			aiPursuitAttack.cpp
* \brief		AI pursuit attack state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise pursuit attack state of AI
*				- Ai to attack while in pursuit
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"
#include "../../Player/PlayerManager.h"


void aiPursuitAttack::OnEnter(aiBlackBoard& bb)
{
	// Cache player
	ptrans = Core::Get().GetComponent<cTransform>(PlayerManager::player);
	prb = Core::Get().GetComponent<cRigidBody>(PlayerManager::player);
	// Cache self components
	rwp = Core::Get().GetComponent<cRangeWeapon>(bb.id);

	_pursuitTimer = 0.0f;
	_minStay = 3.0f + (AERandFloat() * 4.0f);

	aiBase::OnEnter(bb);
}

void aiPursuitAttack::OnUpdate(aiBlackBoard& bb)
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
	Transform::RotateToTarget(trans->_rotation, bb.directionToPlayerN, bb.baseRotationSpeed * g_dt);

	// Check close enough to attack or not
	AEVec2Sub(&_targetPosition, &_futureTargetPosition, &trans->_position);
	_distanceFromTarget = AEVec2Length(&_targetPosition);

	// If close enough to attack
	Attack();
	if (_distanceFromTarget < bb.baseAttackRange)
		ChangeState(STATE_ATTACK);

	_minStay -= g_dt;
	if (_minStay < 0.0f)
		ChangeState(STATE_IDLE);
}

void aiPursuitAttack::OnExit(aiStateList& var)
{
	aiBase::OnExit(var);
}

void aiPursuitAttack::Attack()
{
	rwp->_enemyIsShooting = true;
}