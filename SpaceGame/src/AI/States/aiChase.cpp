/**********************************************************************************
* \file			aiChase.cpp
* \brief		AI chase state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise chase state of AI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void aiChase::OnEnter(aiBlackBoard& bb)
{
	aiBase::OnEnter(bb);

	// Initialize state
	rb->_velocityCap = bb.baseMaxSpeed;
	_minStay = 2.0f + (AERandFloat() * 3.0f);
}

void aiChase::OnUpdate(aiBlackBoard& bb)
{
	rb->_velocity += rb->_acceleration;
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
	_minStay -= g_dt;
	if (_minStay < 0.0f)
		ChangeState((AERandFloat() > 0.5f) ? STATE_PURSUIT : STATE_PURSUITATTACK);
}

void aiChase::OnExit(aiStateList& var)
{
	aiBase::OnExit(var);
}
