#include "aiState.h"

#include "../ECS/Core.h"
#include "../Math/Math.h"
#include "../Global.h"
#include "../Tools/Editor.h"
#include "../Player/PlayerManager.h"

void aiPursuit::Run(const aiBlackBoard& bb, the_variant& var)
{
	switch (innerState)
	{
	case INNER_STATE_ONENTER:

		// Cache self components
		trans = Core::Get().GetComponent<cTransform>(bb.id);
		rb = Core::Get().GetComponent<cRigidBody>(bb.id);

		ptrans = Core::Get().GetComponent<cTransform>(PlayerManager::player);
		prb = Core::Get().GetComponent<cRigidBody>(PlayerManager::player);

		// Initialize state
		attackRange = 200.0f;
		maxSpeed = 150.0f;
		rb->_velocityCap = maxSpeed;
		acceleration = 5.0f;
		rotationSpeed = 30.0f;
		wanderAngle = 0.0f;

		// Change inner state
		innerState = INNER_STATE_ONUPDATE;
		printf("AI is pursuit\n");

		break;
	case INNER_STATE_ONUPDATE:

		rb->_velocity += acceleration;
		Steering::Pursuit(rb->_steeringVector, futurePosition, prb->_velocity, ptrans->_position, prb->_velocityVector, trans->_position, rb->_velocity * g_dt, rb->_velocityVector);
		Steering::Wander(rb->_steeringVector, rb->_velocityDirection, 1.0f, rotationSpeed, wanderAngle, 0.5f);

		// Look at target pos
		Transform::RotateToTarget(trans->_rotation, futurePosition, rotationSpeed * g_dt);

		AEVec2Sub(&targetDistance, &futurePosition, &trans->_position);
		distanceFromTarget = AEVec2Length(&targetDistance);
		// If close enough to attack
		if (distanceFromTarget < attackRange)
		{
			// Change inner state
			innerState = INNER_STATE_ONEXIT;
			var.m_Varient.emplace<aiAttack>();
		}

		break;
	case INNER_STATE_ONEXIT:


		break;
	}
}
