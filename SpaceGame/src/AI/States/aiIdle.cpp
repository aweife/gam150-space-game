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
	switch (bb.type)
	{
	case ENEMY:

		if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange))
			ChangeState(STATE_CHASE);

		break;
	case OBJECTIVE:
	case LEVEL_END:

		if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange/4.0f))
			ChangeState(SPECIAL_ENTER);

		break;
	}
}

void aiIdle::OnExit(aiStateList& var)
{
	aiBase::OnExit(var);
}
