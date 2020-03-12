#pragma once

#include "AEEngine.h"

namespace Steering
{
	void SeekTarget(AEVec2& steering, const AEVec2& playerDir, const f32& velocity, const AEVec2& currentVel);
	void SeekTarget(AEVec2& steering, const AEVec2& selfPos, const AEVec2& targetPos, const f32& velocity, const AEVec2& currentVel);
}

namespace Transform
{
	void RotateToTarget(float& rotation, AEVec2& selfPos, AEVec2& targetPos, const float& speed);
	void RotateToTarget(float& rotation, const AEVec2& desired, const float& speed);
}