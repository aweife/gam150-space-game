#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void bossSpawn::OnEnter(aiBlackBoard& bb)
{
	bossBase::OnEnter(bb);

	_maxSize = trans->_scale;
	AEVec2Scale(&_maxSize, &_maxSize, 2.0f);

	_sizeRatioX = bb.baseMaxSpeed * (trans->_scale.x / _maxSize.x);
	_sizeRatioY = bb.baseMaxSpeed * (trans->_scale.y / _maxSize.y);
}

void bossSpawn::OnUpdate(aiBlackBoard& bb)
{
	if (trans->_scale.x < _maxSize.x && trans->_scale.y < _maxSize.y)
	{
		trans->_scale.x += g_dt * _sizeRatioX;
		trans->_scale.y += g_dt * _sizeRatioY;
	}
	else
		ChangeAttack(BOSS_IDLE);
}

void bossSpawn::OnExit(bossAttackList& var)
{
	trans->_rotation = 0.0f;
	trans->_scale = _maxSize;

	bossBase::OnExit(var);
}