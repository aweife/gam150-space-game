/**********************************************************************************
* \file			bossBase.h
* \brief		Base boss state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise boss behavior of the game
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

struct bossAttackList;

enum ATTACK
{
	BOSS_IDLE,
	BOSS_NORMAL,
	BOSS_HOMING,
	BOSS_MOVE,
	BOSS_RAPID
};

class bossBase
{
public:
	void Run(aiBlackBoard&, bossAttackList&);
protected:
	virtual void OnEnter(aiBlackBoard&);
	virtual void OnUpdate(aiBlackBoard&) = 0;
	virtual void OnExit(bossAttackList&);

	void ChangeAttack(ATTACK);

	INNER_STATE innerState;
	ATTACK nextAttack;

	cTransform* trans;
	cRigidBody* rb;
};