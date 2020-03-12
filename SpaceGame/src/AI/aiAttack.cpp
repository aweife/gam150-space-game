#include "aiState.h"
#include "../ECS/Core.h"
#include "../Math/Math.h"
#include "../Global.h"
#include "../Tools/Console.h"

void aiAttack::Run(const aiBlackBoard& bb, the_variant& var)
{
	switch (innerState)
	{
	case INNER_STATE_ONENTER:

		// Cache self components
		trans = Core::Get().GetComponent<cTransform>(bb.id);
		rb = Core::Get().GetComponent<cRigidBody>(bb.id);
		rwp = Core::Get().GetComponent<cRangeWeapon>(bb.id);

		// Initialise state
		rotationSpeed = 10.0f;

		maxDistance = 900.0f;
		minDistance = 200.0f;

		// Change inner state
		innerState = INNER_STATE_ONUPDATE;

		printf("AI is attacking\n");

		break;
	case INNER_STATE_ONUPDATE:

		// Slowdown
		if (rb->_velocity > rb->_acceleration)
			rb->_velocity *= 0.9f;

		// Always aim at player in this state
		AimAtTarget(bb);

		// Attack with timer
		if (TargetInRange(bb))
		{
			Attack();

			// If too close to player
			if (bb.distanceFromPlayer < minDistance)
			{
				// Change inner state
				innerState = INNER_STATE_ONEXIT;

				// Change state to seek
				var.m_Varient.emplace<aiRetreat>();
			}
		}
		else
		{
			// Change inner state
			innerState = INNER_STATE_ONEXIT;

			// Change state to seek
			var.m_Varient.emplace<aiChase>();
		}


		break;
	case INNER_STATE_ONEXIT:

		Console_Cout("did it go here and how many times?\n");

		break;
	}
}

void aiAttack::AimAtTarget(const aiBlackBoard& bb)
{
	Transform::RotateToTarget(trans->_rotation, bb.directionToPlayerN, rotationSpeed * g_dt);
}

bool aiAttack::TargetInRange(const aiBlackBoard& bb)
{
	// If player is still in range
	return (bb.distanceFromPlayer < maxDistance);
}

void aiAttack::Attack()
{
	rwp->_isShooting = true;
}
