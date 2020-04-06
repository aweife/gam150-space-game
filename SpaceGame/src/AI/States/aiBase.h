/**********************************************************************************
* \file			aiBase.h
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