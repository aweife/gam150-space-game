#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void bossSpawn::OnEnter(aiBlackBoard& bb)
{
	bossBase::OnEnter(bb);

	_initialScale = trans->_scale;
	AEVec2Zero(&trans->_scale);
	trans->_scale.x += g_dt * bb.baseMaxSpeed;
}

void bossSpawn::OnUpdate(aiBlackBoard& bb)
{
	if (trans->_scale.x < _initialScale.x)
		trans->_scale.x += g_dt * bb.baseMaxSpeed;
	else if (trans->_scale.y < _initialScale.y)
		trans->_scale.y += g_dt * bb.baseMaxSpeed;
	else
		ChangeAttack(BOSS_HOMING);

	trans->_rotation += g_dt * bb.baseMaxSpeed * bb.baseRotationSpeed;
}

void bossSpawn::OnExit(bossAttackList& var)
{
	trans->_rotation = 0.0f;
	trans->_scale = _initialScale;

	bossBase::OnExit(var);
}