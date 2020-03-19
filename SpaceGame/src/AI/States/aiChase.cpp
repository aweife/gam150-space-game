#include "../aiState.h"

#include "../../ECS/Core.h"
#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"

void aiChase::Run(aiBlackBoard& bb, aiStateList& var)
{
	switch (innerState)
	{
	case INNER_STATE_ONENTER:

		// Cache self components
		trans = Core::Get().GetComponent<cTransform>(bb.id);
		rb = Core::Get().GetComponent<cRigidBody>(bb.id);

		// Initialize state
		rb->_velocityCap = bb.maxSpeed;
		_chaseTimer = 0.0f;


		// Change inner state
		innerState = INNER_STATE_ONUPDATE;
		printf("AI is chasing\n");

		break;
	case INNER_STATE_ONUPDATE:

		rb->_velocity += bb.acceleration;
		Steering::SeekTarget(rb->_steeringVector, bb.directionToPlayerN, rb->_velocity * g_dt, rb->_velocityVector);
		Steering::Wander(rb->_steeringVector, rb->_velocityDirection, bb.wanderAngle, 1.0f);
		Transform::RotateToTarget(trans->_rotation, bb.directionToPlayerN, bb.rotationSpeed * g_dt);

		// If close enought to attack
		if (bb.distanceFromPlayer < bb.attackRange)
		{
			// Change inner state
			innerState = INNER_STATE_ONEXIT;
			var.states.emplace<aiAttack>();
		}

		// Transit to pursuit
		_chaseTimer += g_dt;
		if (_chaseTimer > 5.0f)
		{
			// Change inner state
			innerState = INNER_STATE_ONEXIT;
			var.states.emplace<aiPursuit>();
		}

		break;
	case INNER_STATE_ONEXIT:


		break;
	}
}
