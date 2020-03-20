#pragma once

#include "../aiBlackBoard.h"
#include "../../ECS/Core.h"
#include "../../Components/cTransform.h"
#include "../../Components/cRigidBody.h"

struct aiStateList;

enum STATE
{
	STATE_ATTACK,
	STATE_CHASE,
	STATE_IDLE,
	STATE_PURSUIT,
	STATE_RETREAT,
};

class aiBase
{
public:
	void Run(aiBlackBoard&, aiStateList&);
protected:
	virtual void OnEnter(aiBlackBoard&);
	virtual void OnUpdate(aiBlackBoard&) = 0;
	virtual void OnExit(aiStateList&);

	void ChangeState(STATE);

	INNER_STATE innerState;
	STATE nextState;

	cTransform* trans;
	cRigidBody* rb;
};