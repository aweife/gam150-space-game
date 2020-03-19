#include "../aiState.h"

#include "../../ECS/Core.h"
#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Console.h"

void aiRetreat::Run(aiBlackBoard& bb, aiStateList& var)
{
	switch (innerState)
	{
	case INNER_STATE_ONENTER:

		// Cache self components
		trans = Core::Get().GetComponent<cTransform>(bb.id);
		rb = Core::Get().GetComponent<cRigidBody>(bb.id);

		_safeDistance = 500.0f + bb.attackRange;
		FindSafePosition(bb);


		// Change inner state
		innerState = INNER_STATE_ONUPDATE;
		printf("AI is retreating\n");

		break;
	case INNER_STATE_ONUPDATE:

		if (AEVec2Distance(&_safePosition, &trans->_position) > 10.0f)
		{
			rb->_velocity += rb->_acceleration;
			Steering::SeekTarget(rb->_steeringVector, trans->_position, _safePosition, rb->_velocity * g_dt, rb->_velocityVector);
			Steering::Wander(rb->_steeringVector, rb->_velocityDirection, bb.wanderAngle, 2.0f);
			Transform::RotateToTarget(trans->_rotation, trans->_position, _safePosition, bb.rotationSpeed * g_dt);
		}
		else
		{
			// Change inner state
			innerState = INNER_STATE_ONEXIT;

			// Change state to seek
			var.states.emplace<aiChase>();
		}

		break;
	case INNER_STATE_ONEXIT:



		break;
	}
}

void aiRetreat::FindSafePosition(const aiBlackBoard& bb)
{
	AEVec2 desired = bb.directionToPlayerN;
	AEVec2Neg(&desired, &desired);
	AEVec2Scale(&desired, &desired, _safeDistance);
	AEVec2Add(&_safePosition, &trans->_position, &desired);
	//AEVec2Set(&_targetPosition, -400.0f, 50.0f);
}
