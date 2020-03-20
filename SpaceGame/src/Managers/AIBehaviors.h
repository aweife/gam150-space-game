/*********************************************************************************
* \file			AIBehaviors.h
* \brief		Commonly used functions to calculate steering behaviors
* \author		Ang Wei Feng, 100% Code Contribution
*
*				Allows multiple ai states to share commonly-used functions
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "AEEngine.h"

namespace Steering
{
	void SeekTarget(AEVec2& steering, const AEVec2& playerDir, const f32& velocity, const AEVec2& currentVel);
	void SeekTarget(AEVec2& steering, const AEVec2& selfPos, const AEVec2& targetPos, const f32& velocity, const AEVec2& currentVel);
	void SetAngle(AEVec2& vector, const float& value);
	void Wander(AEVec2& steering, const AEVec2& currentDir, float& wanderAngle, const float angleChange);
	void Pursuit(AEVec2& steering, AEVec2& futurePosition, const float& prediction, AEVec2& targetPos, AEVec2 targetVel, AEVec2& selfPos, const f32& velocity, const AEVec2& currentVel);
}

namespace Transform
{
	void RotateToTarget(float& rotation, AEVec2& selfPos, AEVec2& targetPos, const float& speed);
	void RotateToTarget(float& rotation, const AEVec2& desired, const float& speed);
}

namespace Check
{
	bool LessThanRange(const float& playerDistance, const float& range);
}