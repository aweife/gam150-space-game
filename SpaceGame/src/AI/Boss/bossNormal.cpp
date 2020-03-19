#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void bossNormal::OnEnter(aiBlackBoard& bb)
{
	bossBase::OnEnter(bb);
}

void bossNormal::OnUpdate(aiBlackBoard& bb)
{
	if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange))
		ChangeAttack(BOSS_NORMAL);
}

void bossNormal::OnExit(bossAttackList& var)
{
	bossBase::OnExit(var);
}