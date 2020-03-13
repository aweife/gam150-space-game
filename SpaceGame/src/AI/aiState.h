/*********************************************************************************
* \file			aiState.h
* \brief		Stores all states and variants of our ai
* \author		Chong Jun Yi, 50% Code Contribution
* \author		Ang Wei Feng, 50% Code Contribution
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
#include "aiChase.h"
#include "aiAttack.h"
#include "aiRetreat.h"
#include "aiPursuit.h"

// For commonly used ai functions
#include "../Managers/AIBehaviors.h"

struct the_variant
{
	std::variant< aiChase, aiAttack, aiRetreat, aiPursuit > m_Varient;
};

#endif
