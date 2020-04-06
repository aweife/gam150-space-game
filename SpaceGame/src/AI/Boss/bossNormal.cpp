#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void bossNormal::OnEnter(aiBlackBoard& bb)
{
	bossBase::OnEnter(bb);

	// Cache self components
	rwp = Core::Get().GetComponent<cRangeWeapon>(bb.id);

	// Init state
	_attackDuration = 3.0f + AERandFloat();
}

void bossNormal::OnUpdate(aiBlackBoard& bb)
{
	_attackDuration -= g_dt;
	if (_attackDuration < 0.0f)
		ChangeAttack(BOSS_IDLE);

	if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange))
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