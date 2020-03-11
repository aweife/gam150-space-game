#include "AIBehaviors.h"
#include "../Math/Math.h"

AEVec2& Steering::SeekTarget(AEVec2& desired, AEVec2& current, const f32& velocity)
{
	// Scale by velocity
	AEVec2Scale(&desired, &desired, velocity);

	// Get steering vector
	AEVec2Sub(&desired, &desired, &current);

	return desired;
}

AEVec2& Steering::SeekTarget(AEVec2& selfPos, AEVec2& targetPos, AEVec2& current, const f32& velocity)
{
	// The directional vector to the target
	AEVec2 desired;
	AEVec2Sub(&desired, &targetPos, &selfPos);
	AEVec2Normalize(&desired, &desired);

	// Scale by velocity
	AEVec2Scale(&desired, &desired, velocity);

	// Get steering vector
	AEVec2Sub(&desired, &desired, &current);

	return desired;
}

AEVec2& Steering::FleeTarget(AEVec2& desired, AEVec2& current, const f32& velocity)
{
	// Flee = -Seek
	AEVec2 steering = SeekTarget(desired, current, velocity);
	AEVec2Neg(&steering, &steering);

	return steering;
}

AEVec2& Steering::FleeTarget(AEVec2& selfPos, AEVec2& targetPos, AEVec2& current, const f32& velocity)
{
	// Flee = -Seek
	AEVec2 steering = SeekTarget(selfPos, targetPos, current, velocity);
	AEVec2Neg(&steering, &steering);

	return steering;
}

/* Transform *****************************************************************/

const f32& Transform::RotateToTarget(AEVec2& selfPos, AEVec2& targetPos, const float& rotation, const float& speed)
{
	// The directional vector to the target
	AEVec2 desired;
	AEVec2Sub(&desired, &targetPos, &selfPos);
	AEVec2Normalize(&desired, &desired);

	// Calculate angle
	float angle = static_cast<float>(atan2(desired.y, desired.x));

	// Face target
	return MBMath_LerpRotation(rotation, angle, speed);
}

const f32& Transform::RotateToTarget(const AEVec2& desired, const float& rotation, const float& speed)
{
	// Calculate angle
	float angle = static_cast<float>(atan2(desired.y, desired.x));

	// Face target
	return MBMath_LerpRotation(rotation, angle, speed);
}
