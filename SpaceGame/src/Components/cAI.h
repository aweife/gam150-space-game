/*********************************************************************************
* \file			cAI.h
* \brief		AI Component
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Responsible for AI component
*				
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
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
