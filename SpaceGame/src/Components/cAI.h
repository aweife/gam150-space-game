#pragma once

#include "../Global.h"
#include "../AI/aiBlackBoard.h"
#include "../AI/aiState.h"


class cAI : Component
{
public:
	float minDistance;
	float maxDistance;

	aiBlackBoard _blackboard;
	the_variant  _currentState;
};
