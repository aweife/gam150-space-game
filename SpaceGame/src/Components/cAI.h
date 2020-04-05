#pragma once

#include "Component.h"
#include "../AI/aiBlackBoard.h"
#include "../AI/aiState.h"

class cAI : public Component
{
public:
	cAI(ENTITY entity, AI_TYPE type) : _blackboard{ entity, type } {}
	aiBlackBoard _blackboard;
	aiStateList  _currentState;
};
