#pragma once

#include "Component.h"
#include "../AI/aiBlackBoard.h"
#include "../AI/aiState.h"

class cAI : public Component
{
public:
	aiBlackBoard _blackboard;
	aiStateList  _currentState;
};
