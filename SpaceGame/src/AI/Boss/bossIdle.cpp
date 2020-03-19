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
	if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange))
		ChangeAttack(BOSS_NORMAL);
}

void bossIdle::OnExit(bossAttackList& var)
{
	bossBase::OnExit(var);
}