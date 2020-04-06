#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void bossIdle::OnEnter(aiBlackBoard& bb)
{
	bossBase::OnEnter(bb);
	_idleTimer = 1.0f + AERandFloat() * 2.0f;
}

void bossIdle::OnUpdate(aiBlackBoard& bb)
{
	_idleTimer -= g_dt;
	if(_idleTimer < 0.0f)
		ChangeAttack(BOSS_MOVE);
}

void bossIdle::OnExit(bossAttackList& var)
{
	bossBase::OnExit(var);
}