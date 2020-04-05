#pragma once

#include "Component.h"
#include "../AI/aiBlackBoard.h"
#include "../AI/aiState.h"

class cBoss : public Component
{
public:
	cBoss(ENTITY entity, AI_TYPE type) : _blackboard{ entity, type } {}
	aiBlackBoard _blackboard;
	bossAttackList  _currentAttack;
};
