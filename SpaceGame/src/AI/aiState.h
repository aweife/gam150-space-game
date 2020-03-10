#ifndef AI_STATE_H
#define AI_STATE_H
#pragma once

#include <variant>
#include "aiChase.h"
#include "aiAttack.h"
#include "aiFleePlayer.h"

struct the_variant
{
	std::variant< aiChase, aiAttack > m_Varient;
};

#endif
