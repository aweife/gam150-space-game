#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void aiIdle::OnEnter(aiBlackBoard& bb)
{
	aiBase::OnEnter(bb);
}

void aiIdle::OnUpdate(aiBlackBoard& bb)
{
	if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange))
		ChangeState(STATE_CHASE);
}

void aiIdle::OnExit(aiStateList& var)
{
	aiBase::OnExit(var);
}
