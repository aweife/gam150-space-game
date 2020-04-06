/**********************************************************************************
* \file			bossMove.cpp
* \brief		Boss move state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Moves the boss slowly towards the target
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void bossMove::OnEnter(aiBlackBoard& bb)
{
	bossBase::OnEnter(bb);

	// Init
	_moveDuration = 3.0f + AERandFloat() * 2.0f;
}

void bossMove::OnUpdate(aiBlackBoard& bb)
{
	rb->_velocity += rb->_acceleration;
	if (rb->_velocity > rb->_velocityCap)
		rb->_velocity = rb->_velocityCap;
	Steering::SeekTarget(rb->_steeringVector, bb.directionToPlayerN, rb->_velocity * g_dt, rb->_velocityVector);

	_moveDuration -= g_dt;
	if (_moveDuration < 0.0f)
		ChangeAttack((AERandFloat() > 0.5f) ? (AERandFloat() > 0.5f ? BOSS_NORMAL : BOSS_HOMING) : (AERandFloat() > 0.5f ? BOSS_NORMAL : BOSS_RAPID));
}

void bossMove::OnExit(bossAttackList& var)
{
	bossBase::OnExit(var);
}