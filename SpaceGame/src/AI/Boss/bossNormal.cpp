/**********************************************************************************
* \file			bossNormal.cpp
* \brief		Boss normal state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise boss normal state
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void bossNormal::OnEnter(aiBlackBoard& bb)
{
	bossBase::OnEnter(bb);

	// Cache self components
	rwp = Core::Get().GetComponent<cRangeWeapon>(bb.id);
}

void bossNormal::OnUpdate(aiBlackBoard& bb)
{
	if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange*2.0f))
		Attack(bb);
}

void bossNormal::OnExit(bossAttackList& var)
{
	bossBase::OnExit(var);
}

void bossNormal::Attack(aiBlackBoard& bb)
{
	rwp->_enemyIsShooting = true;
	rwp->_bossIsShooting = true;
	rwp->_homing = false;
	rwp->_targetPosition = bb.playerLastKnownPosition;
}