/**********************************************************************************
* \file			bossIdle.cpp
* \brief		Boss idle state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise boss idle state
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void bossIdle::OnEnter(aiBlackBoard& bb)
{
	bossBase::OnEnter(bb);
}

void bossIdle::OnUpdate(aiBlackBoard& bb)
{
	if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange*2.0f))
		ChangeAttack(BOSS_HOMING);
}

void bossIdle::OnExit(bossAttackList& var)
{
	bossBase::OnExit(var);
}