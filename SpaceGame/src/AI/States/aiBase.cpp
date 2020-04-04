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
