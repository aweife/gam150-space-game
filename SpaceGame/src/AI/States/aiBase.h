#pragma once

#include "../aiBlackBoard.h"

struct aiStateList;

enum INNER_STATE
{
	INNER_STATE_ONENTER,
	INNER_STATE_ONUPDATE,
	INNER_STATE_ONEXIT,
};

struct aiBase
{
	INNER_STATE innerState;

	virtual void Run( aiBlackBoard&, aiStateList& ) = 0;
};