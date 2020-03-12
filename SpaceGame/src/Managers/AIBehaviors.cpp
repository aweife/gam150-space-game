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
