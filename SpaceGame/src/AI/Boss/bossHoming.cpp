/**********************************************************************************
* \file			bossHoming.cpp
* \brief		Boss homing state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise boss homing state
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void bossHoming::OnEnter(aiBlackBoard& bb)
{
	bossBase::OnEnter(bb);

	// Cache self components
	rwp = Core::Get().GetComponent<cRangeWeapon>(bb.id);

	// Cache original values
	_attackCooldown = rwp->_attackCooldown;
	_delayBetweenAttacks = rwp->_delayBetweenAttacks;
	_numberOfAttacks = rwp->_numberOfAttacks;

	// Init state
	_attackDuration = 10.0f + AERandFloat() * 5.0f;
	rwp->_attackCooldown = 2.0f;
	rwp->_delayBetweenAttacks = 0.0f;
	rwp->_numberOfAttacks = 1;
}

void bossHoming::OnUpdate(aiBlackBoard& bb)
{
	_attackDuration -= g_dt;
	if (_attackDuration < 0.0f)
		ChangeAttack(BOSS_IDLE);

	if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange * 3.0f))
		Attack(bb);
}

void bossHoming::OnExit(bossAttackList& var)
{
	// Reset to original values
	rwp->_attackCooldown = _attackCooldown;
	rwp->_delayBetweenAttacks = _delayBetweenAttacks;
	rwp->_numberOfAttacks = _numberOfAttacks;

	bossBase::OnExit(var);
}

void bossHoming::Attack(aiBlackBoard& bb)
{
	rwp->_enemyIsShooting = true;
	rwp->_bossIsShooting = true;
	rwp->_homing = true;
	rwp->_targetPosition = bb.playerLastKnownPosition;
}