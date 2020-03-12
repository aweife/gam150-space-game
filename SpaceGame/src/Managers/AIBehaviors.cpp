#include "AIBehaviors.h"
#include "../Math/Math.h"

namespace Steering
{
	void SeekTarget(AEVec2& steering, const AEVec2& playerDir, const f32& velocity, const AEVec2& currentVel)
	{
		// The directional vector to the target
		AEVec2 desired = playerDir, current = currentVel;

		// Get desired velocity
		AEVec2Scale(&desired, &desired, velocity);

		// Get steering vector
		AEVec2Sub(&steering, &desired, &current);
	}

	void SeekTarget(AEVec2& steering, const AEVec2& selfPos, const AEVec2& targetPos, const f32& velocity, const AEVec2& currentVel)
	{
		// The directional vector to the target
		AEVec2 desired, self = selfPos, target = targetPos, current = currentVel;
		AEVec2Sub(&desired, &target, &self);
		AEVec2Normalize(&desired, &desired);

		// Get desired velocity
		AEVec2Scale(&desired, &desired, velocity);

		// Get steering vector
		AEVec2Sub(&steering, &desired, &current);
	}

	void SetAngle(AEVec2& vector, const float& value)
	{
		float length = AEVec2Length(&vector);
		vector.x = cosf(value) * length;
		vector.y = sinf(value) * length;
	}

	void Wander(AEVec2& steering, const AEVec2& currentDir, const float circleDistance, const float circleRadius, float& wanderAngle, const float angleChange)
	{
		// Calculate the circle's position
		AEVec2 circleCenter = currentDir;
		AEVec2Scale(&circleCenter, &circleCenter, circleDistance);

		// Calculate displacement force
		AEVec2 displacement = { 0.0f, -1.0f };
		AEVec2Scale(&circleCenter, &circleCenter, circleRadius);

		// Change wanderAngle just a bit, so it
		// won't have the same value in the next game frame.
		SetAngle(displacement, wanderAngle);

		// Change wanderAngle just a bit, so it
		// won't have the same value in the next game frame.
		wanderAngle += AERandFloat() * angleChange - angleChange * 0.5f;

		// Add to steering
		AEVec2 wanderForce;
		AEVec2Add(&wanderForce, &circleCenter, &displacement);
		AEVec2Add(&steering, &steering, &displacement);
	}

	void Pursuit(AEVec2& steering, AEVec2& futurePosition, const float& prediction, AEVec2& targetPos, AEVec2 targetVel, AEVec2& selfPos, const f32& velocity, const AEVec2& currentVel)
	{
		AEVec2 predictionPos;
		AEVec2Scale(&predictionPos, &targetVel, prediction);
		AEVec2Add(&futurePosition, &targetPos, &predictionPos);

		// Seek future position
		SeekTarget(steering, selfPos, futurePosition, velocity, currentVel);
	}
}

/* Transform *****************************************************************/

namespace Transform
{
	void RotateToTarget(float& rotation, AEVec2& selfPos, AEVec2& targetPos, const float& speed)
	{
		// The directional vector to the target
		AEVec2 desired;
		AEVec2Sub(&desired, &targetPos, &selfPos);
		AEVec2Normalize(&desired, &desired);

		// Calculate angle
		float angle = static_cast<float>(atan2(desired.y, desired.x));

		// Face target
		rotation = MBMath_LerpRotation(rotation, angle, speed);
	}

	void RotateToTarget(float& rotation, const AEVec2& desired, const float& speed)
	{
		// Calculate angle
		float angle = static_cast<float>(atan2(desired.y, desired.x));

		// Face target
		rotation = MBMath_LerpRotation(rotation, angle, speed);
	}
}
