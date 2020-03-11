#ifndef AI_STATE_H
#define AI_STATE_H
#pragma once

#include <variant>
#include "aiChase.h"
#include "aiAttack.h"
#include "aiRetreat.h"

// For all states
#include "AIBehaviors.h"

struct the_variant
{
	std::variant< aiChase, aiAttack, aiRetreat > m_Varient;
};

#endif
