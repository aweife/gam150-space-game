#pragma once

#include "aiBlackBoard.h"

struct the_variant;

struct aiBase
{
	enum INNER_STATE
	{
		INNER_STATE_ONENTER,
		INNER_STATE_ONUPDATE,
		INNER_STATE_ONEXIT,
	};
	INNER_STATE innerState;

	virtual void Run( const aiBlackBoard&, the_variant& ) = 0;
};