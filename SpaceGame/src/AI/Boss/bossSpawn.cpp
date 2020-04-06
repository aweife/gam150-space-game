#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void bossSpawn::OnEnter(aiBlackBoard& bb)
{
	bossBase::OnEnter(bb);

	_maxSize = trans->_scale;
	AEVec2Scale(&_maxSize, &_maxSize, 2.0f);

	_sizeRatioX = (_maxSize.x - trans->_scale.x) / bb.baseAcceleration;
	_sizeRatioY = (_maxSize.y - trans->_scale.y) / bb.baseAcceleration;
}

void bossSpawn::OnUpdate(aiBlackBoard& bb)
{
	if (trans->_scale.x < _maxSize.x && trans->_scale.y < _maxSize.y)
	{
		trans->_scale.x += g_dt * g_dt * _sizeRatioX * trans->_scale.x;
		trans->_scale.y += g_dt * g_dt * _sizeRatioY * trans->_scale.y;
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