/*********************************************************************************
* \file			aiState.h
* \brief		Stores all states and variants of our ai
* \author		Ang Wei Feng, 100% Code Contribution
*
*				Responsible for adding components to their component storages
*				and provides a pointer to the component storage
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#ifndef AI_STATE_H
#define AI_STATE_H
#pragma once

#include <variant>

// All AI states
#include "States/aiChase.h"
#include "States/aiAttack.h"
#include "States/aiRetreat.h"
#include "States/aiPursuit.h"
#include "States/aiIdle.h"

// Boss attacks
#include "Boss/bossSpawn.h"
#include "Boss/bossIdle.h"
#include "Boss/bossNormal.h"
#include "Boss/bossHoming.h"

// For commonly used ai functions
#include "../Managers/AIBehaviors.h"

struct aiStateList
{
	std::variant< aiChase, aiPursuit, aiAttack, aiRetreat, aiIdle > states;
};

struct bossAttackList
{
	std::variant< bossSpawn, bossIdle, bossNormal, bossHoming > attacks;
};

#endif
