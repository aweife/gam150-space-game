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