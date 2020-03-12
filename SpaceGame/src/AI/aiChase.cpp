#include "aiState.h"

#include "../ECS/Core.h"
#include "../Math/Math.h"
#include "../Global.h"
#include "../Tools/Editor.h"

void aiChase::Run(const aiBlackBoard& bb, the_variant& var)
{
	switch (innerState)
	{
	case INNER_STATE_ONENTER:

		// Cache self components
		trans = Core::Get().GetComponent<cTransform>(bb.id);
		rb = Core::Get().GetComponent<cRigidBody>(bb.id);

		// Initialize state
		attackRange = 250.0f;
		maxSpeed = 100.0f;
		rb->_velocityCap = maxSpeed;
		acceleration = 5.0f;
		rotationSpeed = 10.0f;
		wanderAngle = 0.0f;
		chaseTimer = 0.0f;

		// Change inner state
		innerState = INNER_STATE_ONUPDATE;
		printf("AI is chasing\n");

		break;
	case INNER_STATE_ONUPDATE:

		rb->_velocity += acceleration;
		Steering::SeekTarget(rb->_steeringVector, bb.directionToPlayerN, rb->_velocity * g_dt, rb->_velocityVector);
		Steering::Wander(rb->_steeringVector, rb->_velocityDirection, 1.0f, rotationSpeed, wanderAngle, 1.0f);
		Transform::RotateToTarget(trans->_rotation, bb.directionToPlayerN, rotationSpeed * g_dt);

		// If close enought to attack
		if (bb.distanceFromPlayer < attackRange)
		{
			// Change inner state
			innerState = INNER_STATE_ONEXIT;
			var.m_Varient.emplace<aiAttack>();
		}

		// Transit to pursuit
		chaseTimer += g_dt;
		if (chaseTimer > 3.0f)
		{
			// Change inner state
			innerState = INNER_STATE_ONEXIT;
			var.m_Varient.emplace<aiPursuit>();
		}

		break;
	case INNER_STATE_ONEXIT:


		break;
	}
}
