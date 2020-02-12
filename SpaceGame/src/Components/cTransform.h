#pragma once

#include "AEEngine.h"

class cTransform
{
public:
	AEMtx33 transform;
	AEVec2 position;
	float rotation;
	AEVec2 scale;

	cTransform();
};