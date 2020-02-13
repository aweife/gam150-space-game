#pragma once
#include "../Components/Component.h"
#include "../Components/cTransform.h"
class cCamera :public Component
{
public:
	bool _isCameraShake = false;
	double _camEffectStartTime = 0.0;
	cTransform* _followTarget = nullptr;
	float _followSpeed;
	float _camVelocity = 0;					//for smoothdamp

	cCamera(cTransform* target = nullptr, float _followSpeed = 0);
	void Init() override;
};

