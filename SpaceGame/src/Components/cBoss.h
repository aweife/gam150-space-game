#pragma once

#include "Component.h"
#include "../AI/aiBlackBoard.h"
#include "../AI/aiState.h"

class cBoss : public Component
{
public:
	aiBlackBoard _blackboard;
	bossAttackList  _currentAttack;
};
