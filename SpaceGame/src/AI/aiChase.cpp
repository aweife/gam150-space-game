#include "aiState.h"
#include "../ECS/Core.h"
#include "../Math/Math.h"
#include "../Global.h"
#include "../Tools/Console.h"

void aiChase::Run(const aiBlackBoard& bb, the_variant& var)
{
	switch (innerState)
	{
	case INNER_STATE_ONENTER:

		// Cache self components
		trans = Core::Get().GetComponent<cTransform>(bb.id);
		rb = Core::Get().GetComponent<cRigidBody>(bb.id);

		// Initialize state
		minDistance = 400.0f;
		attackRange = 300.0f;
		maxSpeed = 100.0f;
		acceleration = 5.0f;

		// Change inner state
		innerState = INNER_STATE_ONUPDATE;

		break;
	case INNER_STATE_ONUPDATE:

		MoveToTarget(bb);

		// If close enought to attack
		if (bb.distanceFromPlayer < attackRange)
		{
			// Change inner state
			innerState = INNER_STATE_ONEXIT;

			// Change state to seek
			var.m_Varient.emplace<aiAttack>();
		}

		break;
	case INNER_STATE_ONEXIT:


		break;
	}
}

void aiChase::RotateToTarget(const aiBlackBoard& bb)
{
	Console_Cout("in seek player!\n");
}

void aiChase::MoveToTarget(const aiBlackBoard& bb)
{
	// Set direction
	AEVec2 desired = bb.directionToPlayerN;
	AEVec2Add(&rb->_velocityDirection, &rb->_velocityDirection, &desired);

	// If too far, accelerate
	if (bb.distanceFromPlayer > minDistance)
		rb->_velocity += acceleration;
	else // Slow down when approaching
		rb->_velocity *= bb.distanceFromPlayer / minDistance;

	// Cap max speed
	if (rb->_velocity > maxSpeed)
		rb->_velocity = maxSpeed;

	// Add to speed
	rb->_velocityVector.x = rb->_velocityDirection.x * rb->_velocity;
	rb->_velocityVector.y = rb->_velocityDirection.y * rb->_velocity;
}
