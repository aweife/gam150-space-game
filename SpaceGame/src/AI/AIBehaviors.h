#pragma once

#include "AEEngine.h"

namespace Steering
{
	AEVec2& SeekTarget(AEVec2& desired, AEVec2& current, const f32& velocity);
	AEVec2& SeekTarget(AEVec2& selfPos, AEVec2& targetPos, AEVec2& current, const f32& velocity);
	AEVec2& FleeTarget(AEVec2& desired, AEVec2& current, const f32& velocity);
	AEVec2& FleeTarget(AEVec2& selfPos, AEVec2& targetPos, AEVec2& current, const f32& velocity);
}

namespace Transform
{
	const f32& RotateToTarget(AEVec2& selfPos, AEVec2& targetPos, const float& rotation, const float& speed);
	const f32& RotateToTarget(const AEVec2& desired, const float& rotation, const float& speed);
}