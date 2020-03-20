#pragma once

#include "AEEngine.h"
#include "Component.h"

class cWarping :public Component
{
public:
	AEVec2 _warpX = { 0 };
	AEVec2 _warpY = { 0 };

	cWarping() = delete;
	cWarping(AEVec2 warpX, AEVec2 warpY);
};