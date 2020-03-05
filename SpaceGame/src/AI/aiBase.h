#pragma once

#include "aiBlackBoard.h"

struct the_variant;

struct aiBase
{
	virtual void Run( const aiBlackBoard&, the_variant& ) = 0;
};