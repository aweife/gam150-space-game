#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"


void aiIdle::OnEnter(aiBlackBoard& bb)
{
	aiBase::OnEnter(bb);

	_idleTimer = 3.0f + AERandFloat() * 2.0f;
}

void aiIdle::OnUpdate(aiBlackBoard& bb)
{
	switch (bb.type)
	{
	case ENEMY:

		_idleTimer -= g_dt;

		if (_idleTimer < 0.0f)
			ChangeState(STATE_IDLEWANDER);

		if (Check::LessThanRange(bb.distanceFromPlayer, bb.baseDetectRange))
			ChangeState((AERandFloat() > 0.5f) ? STATE_CHASE: STATE_CHASEATTACK);

		break;
	case OBJECTIVE:
	case DELIVERY:
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
