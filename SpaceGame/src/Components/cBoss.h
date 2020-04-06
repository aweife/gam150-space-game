/*********************************************************************************
* \file			cBoss.h
* \brief		AI Component
* \author		Ang Wei Feng, 100% Code Contribution
*
*				Responsible for Boss data
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

class cBoss : public Component
{
public:
	cBoss(ENTITY entity, AI_TYPE type) : _blackboard{ entity, type } {}
	aiBlackBoard _blackboard;
	bossAttackList  _currentAttack;
};
