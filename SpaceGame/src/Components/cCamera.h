#pragma once
#include "../Components/Component.h"
#include "../Components/cTransform.h"
class cCamera :public Component
{
public:
	bool _isCameraShake = false;
	double _camEffectStartTime = 0.0;
	cTransform* _followTarget = nullptr;

	cCamera(cTransform* target = nullptr);
	void Init() override;
};

