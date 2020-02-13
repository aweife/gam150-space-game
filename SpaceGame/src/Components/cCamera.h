#pragma once

#include "Component.h"
#include "cTransform.h"

class cCamera :public Component
{
public:
	bool isCameraShake = false;
	double camEffectStartTime = 0.0;
	cTransform* followTarget = nullptr;

	cCamera();
	void Init() override;
};

