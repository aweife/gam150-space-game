#pragma once

#include "../Global.h"
#include "../AI/aiBlackBoard.h"
#include "../AI/aiState.h"


class cAI : public Component
{
public:
	aiBlackBoard _blackboard;
	the_variant  _currentState;
};
