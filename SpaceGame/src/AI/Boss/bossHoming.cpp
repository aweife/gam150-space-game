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
}

void bossHoming::OnUpdate(aiBlackBoard& bb)
{
	if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange * 3.0f))
		Attack(bb);
}

void bossHoming::OnExit(bossAttackList& var)
{
	bossBase::OnExit(var);
}

void bossHoming::Attack(aiBlackBoard& bb)
{
	rwp->_enemyIsShooting = true;
	rwp->_bossIsShooting = true;
	rwp->_homing = true;
	rwp->_targetPosition = bb.playerLastKnownPosition;
}