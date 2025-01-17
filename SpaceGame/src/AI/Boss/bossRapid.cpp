#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void bossRapid::OnEnter(aiBlackBoard& bb)
{
	bossBase::OnEnter(bb);

	// Cache self components
	rwp = Core::Get().GetComponent<cRangeWeapon>(bb.id);

	// Cache original values
	_attackCooldown = rwp->_attackCooldown;
	_delayBetweenAttacks = rwp->_delayBetweenAttacks;
	_numberOfAttacks = rwp->_numberOfAttacks;

	// Init state
	_attackDuration = 5.0f + AERandFloat()*5.0f;
	rwp->_attackCooldown = 3.0f;
	rwp->_delayBetweenAttacks = 0.1f;
	rwp->_numberOfAttacks = 10;
}

void bossRapid::OnUpdate(aiBlackBoard& bb)
{
	_attackDuration -= g_dt;
	if (_attackDuration < 0.0f)
		ChangeAttack(BOSS_IDLE);

	if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange * 2.0f))
		Attack(bb);
}

void bossRapid::OnExit(bossAttackList& var)
{
	// Reset to original values
	rwp->_attackCooldown = _attackCooldown;
	rwp->_delayBetweenAttacks = _delayBetweenAttacks;
	rwp->_numberOfAttacks = _numberOfAttacks;

	bossBase::OnExit(var);
}

void bossRapid::Attack(aiBlackBoard& bb)
{
	rwp->_enemyIsShooting = true;
	rwp->_bossIsShooting = true;
	rwp->_homing = false;
	rwp->_targetPosition = bb.playerLastKnownPosition;
}