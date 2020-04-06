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

	STATE_CHASEATTACK,
	STATE_PURSUITATTACK,
	STATE_RETREATATTACK,
	STATE_IDLEWANDER,

	SPECIAL_ENTER,
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

	float _minStay;

	cTransform* trans;
	cRigidBody* rb;
};