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
