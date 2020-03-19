#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void bossSpawn::OnEnter(aiBlackBoard& bb)
{
	bossBase::OnEnter(bb);

	trans->_scale = { 0.0f, 0.0f };
}

void bossSpawn::OnUpdate(aiBlackBoard& bb)
{
	
}

void bossSpawn::OnExit(bossAttackList& var)
{
	bossBase::OnExit(var);
}