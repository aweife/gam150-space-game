#pragma once

#include "Component.h"
#include "cTransform.h"

class cCamera :public Component
{
public:
	bool _isCameraShake = false;
	double _camEffectStartTime = 0.0;
	cTransform* _followTarget = nullptr;
	float _followSpeed;							//the cap speed for camera follow
	float _camVelocityX = 0;					//for smoothdamp increments
	float _camVelocityY = 0;					//for smoothdamp increments

	cCamera(cTransform* target = nullptr, float _followSpeed = 0);
};

