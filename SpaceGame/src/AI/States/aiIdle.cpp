/**********************************************************************************
* \file			aiIdle.cpp
* \brief		AI idle state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise idle state of AI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
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
			ChangeState((AERandFloat() > 0.5f) ? STATE_CHASE : STATE_IDLEWANDER);

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
