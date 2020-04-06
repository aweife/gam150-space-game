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
	_moveDuration -= g_dt;
	if (_moveDuration < 0.0f)
		//ChangeAttack((AERandFloat() > 0.5f) ? (AERandFloat() > 0.5f ? BOSS_NORMAL : BOSS_HOMING) : BOSS_IDLE);
		ChangeAttack((AERandFloat() > 0.5f) ? BOSS_NORMAL : BOSS_IDLE);
}

void bossMove::OnExit(bossAttackList& var)
{
	bossBase::OnExit(var);
}