/**********************************************************************************
* \file			bossBase.cpp
* \brief		Base boss state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise boss behavior of the game
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "bossBase.h"
#include "../aiState.h"

void bossBase::Run(aiBlackBoard& bb, bossAttackList& var)
{
	switch (innerState)
	{
	case INNER_STATE_ONENTER:
		OnEnter(bb);
		break;
	case INNER_STATE_ONUPDATE:
		OnUpdate(bb);
		break;
	case INNER_STATE_ONEXIT:
		OnExit(var);
		break;
	}
}

void bossBase::OnEnter(aiBlackBoard& bb)
{
	// Cache common components
	trans = Core::Get().GetComponent<cTransform>(bb.id);
	rb = Core::Get().GetComponent<cRigidBody>(bb.id);

	// Change inner state
	innerState = INNER_STATE_ONUPDATE;
}

void bossBase::OnExit(bossAttackList& var)
{
	switch (nextAttack)
	{
	case BOSS_IDLE:
		var.attacks.emplace<bossIdle>();
		break;
	case BOSS_NORMAL:
		var.attacks.emplace<bossNormal>();
		break;
	case BOSS_HOMING:
		var.attacks.emplace<bossHoming>();
		break;
	case BOSS_MOVE:
		var.attacks.emplace<bossMove>();
		break;
	case BOSS_RAPID:
		var.attacks.emplace<bossRapid>();
		break;
	default:
		var.attacks.emplace<bossIdle>();
		break;
	}
}

void bossBase::ChangeAttack(ATTACK attack)
{
	innerState = INNER_STATE_ONEXIT;
	nextAttack = attack;
}
