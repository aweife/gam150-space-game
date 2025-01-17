/*********************************************************************************
* \file			cCamera.h
* \brief		Camera Component
* \author		Jun Yi,		Chong,		100% Code Contribution
*
*				Responsible for Camera component
*
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "Component.h"
#include "cTransform.h"

class cCamera :public Component
{
public:
	bool _isdynamic = true;
	bool _isCameraShake = false;
	float _camEffectStartTime = 0.0;
	float _camEffectDuration = 0.0;
	float _camEffectSpeed = 0.0;

	AEVec2			_camOffsetPos = { 0,0 };
	AEVec2			_camOffsetTarget = { 0,0 };
	cTransform*		_followTarget = nullptr;
	float			_followSpeed;							//the cap speed for camera follow
	float			_camVelocityX = 0;					//for smoothdamp increments
	float			_camVelocityY = 0;					//for smoothdamp increments

	cCamera(cTransform* target = nullptr, float _followSpeed = 0, bool dynamic = true);
};

