/**********************************************************************************
* \file			aiBase.cpp
* \brief		AI chase state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Contains the base class for all ai states to inherit from
*				- Do state transition here
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "aiBase.h"
#include "../aiState.h"

void aiBase::Run(aiBlackBoard& bb, aiStateList& var)
{
	switch (innerState)
	{
	case INNER_STATE_ONENTER:
		OnEnter(bb);
		break;
	case INNER_STATE_ONUPDATE:
		OnUpdate(bb);
		break;
	case INNER_STATE_ONEXIT:
		OnExit(var);
		break;
	}
}

void aiBase::OnEnter(aiBlackBoard& bb)
{
	// Cache common components
	trans = Core::Get().GetComponent<cTransform>(bb.id);
	rb = Core::Get().GetComponent<cRigidBody>(bb.id);

	// Change inner state
	innerState = INNER_STATE_ONUPDATE;
}


void aiBase::OnExit(aiStateList& var)
{
	switch (nextState)
	{
	case STATE_CHASE:
		var.states.emplace<aiChase>();
		break;
	case STATE_ATTACK:
		var.states.emplace<aiAttack>();
		break;
	case STATE_PURSUIT:
		var.states.emplace<aiPursuit>();
		break;
	case STATE_RETREAT:
		var.states.emplace<aiRetreat>();
		break;
	case STATE_IDLE:
		var.states.emplace<aiIdle>();
		break;
	case STATE_CHASEATTACK:
		var.states.emplace<aiChaseAttack>();
		break;
	case STATE_PURSUITATTACK:
		var.states.emplace<aiPursuitAttack>();
		break;
	case STATE_RETREATATTACK:
		var.states.emplace<aiRetreatAttack>();
		break;
	case STATE_IDLEWANDER:
		var.states.emplace<aiIdleWander>();
		break;
	case SPECIAL_ENTER:
		var.states.emplace<objEnter>();
		break;
	default:
		var.states.emplace<aiIdle>();
		break;
	}
}

void aiBase::ChangeState(STATE state)
{
	innerState = INNER_STATE_ONEXIT;
	nextState = state;
}
