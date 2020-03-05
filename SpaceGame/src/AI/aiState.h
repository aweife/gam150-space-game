#ifndef AI_STATE_H
#define AI_STATE_H
#pragma once

#include <variant>
#include "aiSeekPlayer.h"
#include "aiFleePlayer.h"

struct the_variant
{
	std::variant< aiSeekPlayer, aiFleePlayer > m_Varient;
};

#endif
